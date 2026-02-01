#include "fortnite_replay/stores/header_store.hpp"
#include "fortnite_replay/replay.hpp"

namespace fortnite_replay {

HeaderStore::HeaderStore(const Replay *replay) : m_replay(replay) {}

bool HeaderStore::exists() const { return get() != nullptr; }

const HeaderChunk *HeaderStore::get() const {
  return m_replay->header_chunk();
}

std::optional<uint32_t> HeaderStore::networkVersion() const {
  if (auto *header = get()) {
    return header->network_version;
  }
  return std::nullopt;
}

std::optional<uint32_t> HeaderStore::networkChecksum() const {
  if (auto *header = get()) {
    return header->network_checksum;
  }
  return std::nullopt;
}

std::optional<uint32_t> HeaderStore::engineNetworkVersion() const {
  if (auto *header = get()) {
    return header->engine_network_version;
  }
  return std::nullopt;
}

std::optional<uint32_t> HeaderStore::gameNetworkProtocolVersion() const {
  if (auto *header = get()) {
    return header->game_network_protocol_version;
  }
  return std::nullopt;
}

std::optional<std::string> HeaderStore::engineVersion() const {
  if (auto *header = get()) {
    if (header->engine_version.has_value()) {
      return header->engine_version->to_string();
    }
  }
  return std::nullopt;
}

std::optional<std::string> HeaderStore::guid() const {
  if (auto *header = get()) {
    return header->guid;
  }
  return std::nullopt;
}

std::optional<RecordingMetadata> HeaderStore::recordingMetadata() const {
  if (auto *header = get()) {
    return header->recording_metadata;
  }
  return std::nullopt;
}

std::vector<std::string> HeaderStore::levelNames() const {
  std::vector<std::string> result;
  if (auto *header = get()) {
    for (const auto &level : header->levels) {
      result.push_back(level.name);
    }
  }
  return result;
}

std::vector<LevelInfo> HeaderStore::levels() const {
  if (auto *header = get()) {
    return header->levels;
  }
  return {};
}

std::optional<ReplayHeaderFlags> HeaderStore::flags() const {
  if (auto *header = get()) {
    return header->flags;
  }
  return std::nullopt;
}

std::vector<std::string> HeaderStore::gameSpecificData() const {
  if (auto *header = get()) {
    return header->game_specific_data;
  }
  return {};
}

std::optional<PackageVersionInfo> HeaderStore::packageVersionInfo() const {
  if (auto *header = get()) {
    return header->package_version_info;
  }
  return std::nullopt;
}

std::vector<CustomVersion> HeaderStore::customVersions() const {
  if (auto *header = get()) {
    return header->custom_versions;
  }
  return {};
}

} // namespace fortnite_replay
