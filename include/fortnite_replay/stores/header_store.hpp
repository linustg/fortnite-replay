#ifndef FORTNITE_REPLAY_STORES_HEADER_STORE_HPP
#define FORTNITE_REPLAY_STORES_HEADER_STORE_HPP

#include "fortnite_replay/header_chunk.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace fortnite_replay {

class Replay;

/**
 * Store providing convenient access to header information
 */
class HeaderStore {
public:
  /**
   * Check if header chunk exists
   */
  bool exists() const;

  /**
   * Get the raw header chunk (nullptr if doesn't exist)
   */
  const HeaderChunk *get() const;

  /**
   * Get network version
   */
  std::optional<uint32_t> networkVersion() const;

  /**
   * Get network checksum
   */
  std::optional<uint32_t> networkChecksum() const;

  /**
   * Get engine network version
   */
  std::optional<uint32_t> engineNetworkVersion() const;

  /**
   * Get game network protocol version
   */
  std::optional<uint32_t> gameNetworkProtocolVersion() const;

  /**
   * Get engine version as formatted string (e.g., "4.27.2-12345678")
   */
  std::optional<std::string> engineVersion() const;

  /**
   * Get GUID
   */
  std::optional<std::string> guid() const;

  /**
   * Get recording metadata
   */
  std::optional<RecordingMetadata> recordingMetadata() const;

  /**
   * Get level names
   */
  std::vector<std::string> levelNames() const;

  /**
   * Get level infos (names and times)
   */
  std::vector<LevelInfo> levels() const;

  /**
   * Get replay header flags
   */
  std::optional<ReplayHeaderFlags> flags() const;

  /**
   * Get game-specific data
   */
  std::vector<std::string> gameSpecificData() const;

  /**
   * Get package version info
   */
  std::optional<PackageVersionInfo> packageVersionInfo() const;

  /**
   * Get custom versions
   */
  std::vector<CustomVersion> customVersions() const;

private:
  friend class Replay;
  explicit HeaderStore(const Replay *replay);

  const Replay *m_replay;
};

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_STORES_HEADER_STORE_HPP
