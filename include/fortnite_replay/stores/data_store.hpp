#ifndef FORTNITE_REPLAY_STORES_DATA_STORE_HPP
#define FORTNITE_REPLAY_STORES_DATA_STORE_HPP

#include "fortnite_replay/data_chunk.hpp"
#include <cstdint>
#include <optional>
#include <vector>

namespace fortnite_replay {

class Replay;

/**
 * Store providing access to data chunks (replay frames) with time-based
 * queries
 */
class DataStore {
public:
  /**
   * Get all data chunks
   */
  std::vector<const DataChunk *> all() const;

  /**
   * Find frame at specific time (returns frame containing this timestamp)
   */
  std::optional<const DataChunk *> frameAtTime(uint32_t time_ms) const;

  /**
   * Get frames within a time range (inclusive)
   */
  std::vector<const DataChunk *> framesInRange(uint32_t start_ms,
                                                uint32_t end_ms) const;

  /**
   * Get total number of frames
   */
  size_t count() const;

  /**
   * Get total duration across all frames in milliseconds
   */
  uint32_t totalDuration() const;

  /**
   * Iterator support for range-based for loops
   */
  using const_iterator = std::vector<const DataChunk *>::const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

private:
  friend class Replay;
  explicit DataStore(const Replay *replay);

  const Replay *m_replay;
  mutable std::vector<const DataChunk *>
      m_cached_chunks; // Cached for iterator support
};

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_STORES_DATA_STORE_HPP
