#include "fortnite_replay/event_parser.hpp"
#include "fortnite_replay.h"
#include "fortnite_replay/crypto.hpp"
#include "fortnite_replay/event.hpp"
#include "fortnite_replay/utils.hpp"
#include <stdexcept>
#include <vector>

namespace fortnite_replay {

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

Event parse_event_chunk(const fortnite_replay_t::event_chunk_t *event_chunk,
                        std::span<const uint8_t> encryption_key,
                        bool is_encrypted) {
  if (!event_chunk) {
    throw std::runtime_error("Event chunk is null");
  }

  Event event;
  event.id = extract_fstring(event_chunk->id());
  event.event_type =
      Utils::string_to_event_type(extract_fstring(event_chunk->group()));
  event.metadata = extract_fstring(event_chunk->metadata());
  event.start_time_ms = event_chunk->start_time();
  event.end_time_ms = event_chunk->end_time();

  auto raw_data{string_to_bytes(event_chunk->data())};

  ReplayDataProcessor processor;
  auto result{processor.set_encryption_key(encryption_key)};
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
  auto processed_data_result{
      processor.process(std::span<const uint8_t>{raw_data.data(), raw_data.size()},
                       is_encrypted,
                       false)}; // Event chunks are never compressed
  if (!processed_data_result.has_value()) {
    throw std::runtime_error("Failed to process event chunk data");
  }
  event.data = processed_data_result.value();

  switch (event.event_type) {
  case EventType::PlayerElimination: {
    // Parse PlayerEliminated event data
    break;
  }
  case EventType::MatchStats: {
    // Parse MatchStats event data
    break;
  }
  case EventType::TeamStats: {
    // Parse TeamStats event data
    break;
  }
  case EventType::EncryptionKey: {
    // Parse EncryptionKey event data
    break;
  }
  case EventType::CharacterSample: {
    // Parse CharacterSample event data
    break;
  }
  case EventType::ZoneUpdate: {
    // Parse ZoneUpdate event data
    break;
  }
  case EventType::BattleBus: {
    // Parse BattleBus event data
    break;
  }
  default:
    break;
  }

  return event;
}

} // namespace fortnite_replay
