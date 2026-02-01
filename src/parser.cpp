#include "fortnite_replay/parser.hpp"
#include "fortnite_replay.h"
#include "fortnite_replay/crypto.hpp"
#include "fortnite_replay/event_chunk.hpp"
#include "fortnite_replay/utils.hpp"
#include <iostream>
#include <span>

namespace fortnite_replay {

FortniteReplayParser::FortniteReplayParser() = default;
FortniteReplayParser::~FortniteReplayParser() = default;

FortniteReplayParser::FortniteReplayParser(FortniteReplayParser &&) noexcept =
    default;
FortniteReplayParser &
FortniteReplayParser::operator=(FortniteReplayParser &&) noexcept = default;

bool FortniteReplayParser::parse(const std::string &filepath) {
  m_replay.reset();
  m_stream.reset();
  m_file.reset();

  m_file = std::make_unique<std::ifstream>(filepath, std::ios::binary);
  if (!m_file->is_open()) {
    return false;
  }

  try {
    m_stream = std::make_unique<kaitai::kstream>(m_file.get());
    m_replay = std::make_unique<fortnite_replay_t>(m_stream.get());
  } catch (const std::exception &e) {
    std::cerr << "Parse error: " << e.what() << std::endl;
    m_replay.reset();
    return false;
  }

  return true;
}

std::string FortniteReplayParser::magic() const {
  return m_replay ? m_replay->replay_info()->magic() : "";
}

uint32_t FortniteReplayParser::file_version() const {
  return m_replay ? m_replay->replay_info()->file_version() : -1;
}

uint32_t FortniteReplayParser::length_in_ms() const {
  return m_replay ? m_replay->replay_info()->length_in_ms() : 0;
}

uint32_t FortniteReplayParser::network_version() const {
  return m_replay ? m_replay->replay_info()->network_version() : 0;
}

uint32_t FortniteReplayParser::changelist() const {
  return m_replay ? m_replay->replay_info()->changelist() : 0;
}

std::string FortniteReplayParser::friendly_name() const {
  if (!m_replay || !m_replay->replay_info()->friendly_name()) {
    return "";
  }
  if (m_replay->replay_info()->friendly_name()->value_ascii().size() > 0) {
    return m_replay->replay_info()->friendly_name()->value_ascii();
  }
  return m_replay->replay_info()->friendly_name()->value_unicode();
}

bool FortniteReplayParser::is_live() const {
  return m_replay ? (m_replay->replay_info()->is_live() != 0) : false;
}

uint64_t FortniteReplayParser::timestamp() const {
  return m_replay ? m_replay->replay_info()->timestamp() : 0;
}

bool FortniteReplayParser::is_compressed() const {
  return m_replay ? (m_replay->replay_info()->is_compressed() != 0) : false;
}

namespace {
std::string extract_fstring(const fortnite_replay_t::fstring_t *fstr) {
  if (!fstr)
    return "";
  if (!fstr->value_ascii().empty())
    return fstr->value_ascii();
  return fstr->value_unicode();
}

std::vector<uint8_t> string_to_bytes(const std::string &str) {
  return std::vector<uint8_t>(str.begin(), str.end());
}
} // namespace

Replay FortniteReplayParser::replay() {
  Replay result;

  if (!m_replay)
    return result;

  // Populate ReplayInfo from replay_info header
  auto *info = m_replay->replay_info();
  if (info) {
    result.info().file_version = info->file_version();
    result.info().length_ms = info->length_in_ms();
    result.info().network_version = info->network_version();
    result.info().changelist = info->changelist();
    result.info().friendly_name = extract_fstring(info->friendly_name());
    result.info().is_live = info->is_live() != 0;

    if (!info->_is_null_timestamp())
      result.info().timestamp = info->timestamp();

    if (!info->_is_null_is_compressed())
      result.info().is_compressed = info->is_compressed() != 0;

    if (!info->_is_null_is_encrypted())
      result.info().is_encrypted = info->is_encrypted() != 0;

    if (!info->_is_null_encryption_key())
      result.info().encryption_key = string_to_bytes(info->encryption_key());

    // Custom versions from info header
    if (!info->_is_null_custom_versions() && info->custom_versions()) {
      for (const auto *cv : *info->custom_versions()->entries()) {
        result.info().custom_versions.push_back(
            CustomVersion{cv->guid(), cv->version()});
      }
    }
  }

  // Process chunks
  if (m_replay->chunks()) {
    for (const auto *chunk : *m_replay->chunks()) {
      if (!chunk || !chunk->chunk_data())
        continue;

      switch (chunk->chunk_type()) {
      case fortnite_replay_t::REPLAY_CHUNK_TYPE_HEADER: {
        auto *header_chunk = static_cast<fortnite_replay_t::header_chunk_t *>(
            chunk->chunk_data());
        if (!header_chunk)
          break;

        auto &header = result.add_chunk<HeaderChunk>();
        header.network_version = header_chunk->network_version();
        header.network_checksum = header_chunk->network_checksum();
        header.engine_network_version = header_chunk->engine_network_version();
        header.game_network_protocol_version =
            header_chunk->game_network_protocol_version();

        if (!header_chunk->_is_null_guid())
          header.guid = header_chunk->guid();

        if (!header_chunk->_is_null_version_full() &&
            header_chunk->version_full()) {
          auto *ver = header_chunk->version_full();
          header.engine_version =
              EngineVersion{ver->major(), ver->minor(), ver->patch(),
                            ver->changelist(), extract_fstring(ver->branch())};
        }

        if (!header_chunk->_is_null_recording_metadata() &&
            header_chunk->recording_metadata()) {
          auto *meta = header_chunk->recording_metadata();
          header.recording_metadata =
              RecordingMetadata{meta->ue4_version(), meta->ue5_version(),
                                meta->package_version_licensee_ue()};
        }

        if (header_chunk->level_names_and_times() &&
            header_chunk->level_names_and_times()->entries()) {
          for (const auto *level :
               *header_chunk->level_names_and_times()->entries()) {
            header.levels.push_back(
                LevelInfo{extract_fstring(level->name()), level->time()});
          }
        }

        if (!header_chunk->_is_null_flags())
          header.flags = ReplayHeaderFlags::from_bitmask(header_chunk->flags());

        if (header_chunk->game_specific_data() &&
            header_chunk->game_specific_data()->entries()) {
          for (const auto *str :
               *header_chunk->game_specific_data()->entries()) {
            header.game_specific_data.push_back(extract_fstring(str));
          }
        }

        if (!header_chunk->_is_null_package_version_info() &&
            header_chunk->package_version_info()) {
          auto *pkg = header_chunk->package_version_info();
          header.package_version_info = PackageVersionInfo{
              pkg->min_record_hz(),
              pkg->max_record_hz(),
              pkg->frame_limit_in_ms(),
              pkg->checkpoint_limit_in_ms(),
              extract_fstring(pkg->platform()),
              pkg->build_config(),
              static_cast<uint8_t>(pkg->build_target_type())};
        }

        if (!header_chunk->_is_null_custom_versions() &&
            header_chunk->custom_versions()) {
          for (const auto *cv : *header_chunk->custom_versions()->entries()) {
            header.custom_versions.push_back(
                CustomVersion{cv->guid(), cv->version()});
          }
        }
        break;
      }

      case fortnite_replay_t::REPLAY_CHUNK_TYPE_REPLAY_DATA: {
        auto *data_chunk =
            static_cast<fortnite_replay_t::replay_data_chunk_t *>(
                chunk->chunk_data());
        if (!data_chunk)
          break;

        auto &frame = result.add_chunk<DataChunk>();
        if (!data_chunk->_is_null_start_time())
          frame.start_time_ms = data_chunk->start_time();
        if (!data_chunk->_is_null_end_time())
          frame.end_time_ms = data_chunk->end_time();
        if (!data_chunk->_is_null_data_length())
          frame.data_length = data_chunk->data_length();
        if (!data_chunk->_is_null_memory_size_in_bytes())
          frame.memory_size_bytes = data_chunk->memory_size_in_bytes();
        frame.data = string_to_bytes(data_chunk->data());
        break;
      }

      case fortnite_replay_t::REPLAY_CHUNK_TYPE_CHECKPOINT: {
        auto *cp_chunk = static_cast<fortnite_replay_t::checkpoint_chunk_t *>(
            chunk->chunk_data());
        if (!cp_chunk)
          break;

        auto &checkpoint = result.add_chunk<CheckpointChunk>();
        checkpoint.id = extract_fstring(cp_chunk->id());
        checkpoint.group = extract_fstring(cp_chunk->group());
        checkpoint.metadata = extract_fstring(cp_chunk->metadata());
        checkpoint.start_time_ms = cp_chunk->start_time();
        checkpoint.end_time_ms = cp_chunk->end_time();
        checkpoint.data = string_to_bytes(cp_chunk->data());
        break;
      }

      case fortnite_replay_t::REPLAY_CHUNK_TYPE_EVENT: {
        auto *event_chunk = static_cast<fortnite_replay_t::event_chunk_t *>(
            chunk->chunk_data());
        if (!event_chunk)
          break;

        auto &event = result.add_chunk<EventChunk>();
        event.id = extract_fstring(event_chunk->id());
        event.event_type =
            Utils::string_to_event_type(extract_fstring(event_chunk->group()));
        event.metadata = extract_fstring(event_chunk->metadata());
        event.start_time_ms = event_chunk->start_time();
        event.end_time_ms = event_chunk->end_time();

        auto raw_data{string_to_bytes(event_chunk->data())};

        ReplayDataProcessor processor;
        auto key{std::span<const uint8_t>{
            reinterpret_cast<const uint8_t *>(
                m_replay->replay_info()->encryption_key().data()),
            m_replay->replay_info()->encryption_key().size()}};

        auto result{processor.set_encryption_key(key)};
        if (!result.has_value()) {
          throw std::runtime_error(
              "Failed to set encryption key for event chunk processing");
        }
        std::unique_ptr<Decompressor> decompressor =
            std::make_unique<OodleDecompressor>();

        if (!decompressor->is_available()) {
          throw std::runtime_error("Oodle decompressor not available - cannot "
                                   "decompress replay data");
        }

        processor.set_decompressor(std::move(decompressor));
        // Event chunks are NEVER compressed, only encrypted
        auto processed_data_result{processor.process(
            std::span<const uint8_t>{raw_data.data(), raw_data.size()},
            m_replay->replay_info()->is_encrypted(),
            false)}; // Event chunks are never compressed
        if (!processed_data_result.has_value()) {
          throw std::runtime_error("Failed to process event chunk data");
        }
        event.data = processed_data_result.value();
        break;
      }

      default:
        break;
      }
    }
  }

  return result;
}

} // namespace fortnite_replay
