#ifndef FORTNITE_REPLAY_HEADER_CHUNK_HPP
#define FORTNITE_REPLAY_HEADER_CHUNK_HPP

#include "chunk.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace fortnite_replay {

/**
 * Replay header flags
 */
struct ReplayHeaderFlags {
  bool client_recorded = false;
  bool has_streaming_fixes = false;
  bool delta_checkpoints = false;
  bool game_specific_frame_data = false;
  bool replay_connection = false;
  bool actor_prioritization_enabled = false;
  bool net_relevancy_enabled = false;
  bool async_recorded = false;

  static ReplayHeaderFlags from_bitmask(uint32_t flags) {
    return ReplayHeaderFlags{.client_recorded = (flags & 1) != 0,
                             .has_streaming_fixes = (flags & 2) != 0,
                             .delta_checkpoints = (flags & 4) != 0,
                             .game_specific_frame_data = (flags & 8) != 0,
                             .replay_connection = (flags & 16) != 0,
                             .actor_prioritization_enabled = (flags & 32) != 0,
                             .net_relevancy_enabled = (flags & 64) != 0,
                             .async_recorded = (flags & 128) != 0};
  }
};

/**
 * Custom version entry (GUID + version number)
 */
struct CustomVersion {
  std::string guid; // 16 bytes as string
  int32_t version = 0;
};

/**
 * Engine version information (major.minor.patch)
 */
struct EngineVersion {
  uint16_t major = 0;
  uint16_t minor = 0;
  uint16_t patch = 0;
  uint32_t changelist = 0;
  std::string branch;

  std::string to_string() const {
    return std::to_string(major) + "." + std::to_string(minor) + "." +
           std::to_string(patch);
  }
};

/**
 * Level/map information with time offset
 */
struct LevelInfo {
  std::string name;
  uint32_t time_ms = 0;
};

/**
 * Package version and platform information
 */
struct PackageVersionInfo {
  float min_record_hz = 0.0f;
  float max_record_hz = 0.0f;
  float frame_limit_ms = 0.0f;
  float checkpoint_limit_ms = 0.0f;
  std::string platform;
  uint8_t build_config = 0;
  uint8_t build_target_type =
      0; // 0=Unknown, 1=Game, 2=Server, 3=Client, 4=Editor, 5=Program
};

/**
 * Recording metadata (UE4/UE5 version info)
 */
struct RecordingMetadata {
  uint32_t ue4_version = 0;
  uint32_t ue5_version = 0;
  uint32_t package_version_licensee_ue = 0;
};

/**
 * Header chunk containing network/version information
 */
class HeaderChunk : public Chunk {
public:
  HeaderChunk() = default;

  ChunkType type() const override { return ChunkType::Header; }
  const char *type_name() const override { return "Header"; }

  // Network information
  uint32_t network_version = 0;
  uint32_t network_checksum = 0;
  uint32_t engine_network_version = 0;
  uint32_t game_network_protocol_version = 0;
  std::string guid; // 16 bytes

  // Version information
  std::optional<EngineVersion> engine_version;
  std::optional<RecordingMetadata> recording_metadata;
  std::vector<CustomVersion> custom_versions;

  // Level information
  std::vector<LevelInfo> levels;

  // Flags and metadata
  ReplayHeaderFlags flags;
  std::vector<std::string> game_specific_data;
  std::optional<PackageVersionInfo> package_version_info;
};

// Type alias for backward compatibility
using ReplayHeader = HeaderChunk;

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_HEADER_CHUNK_HPP
