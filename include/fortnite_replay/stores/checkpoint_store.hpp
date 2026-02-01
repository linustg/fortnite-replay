#ifndef FORTNITE_REPLAY_STORES_CHECKPOINT_STORE_HPP
#define FORTNITE_REPLAY_STORES_CHECKPOINT_STORE_HPP

#include "fortnite_replay/checkpoint_chunk.hpp"
#include <cstdint>
#include <optional>
#include <vector>

namespace fortnite_replay {

class Replay;

/**
 * Store providing access to checkpoint chunks with time-based queries
 */
class CheckpointStore {
public:
  /**
   * Get all checkpoints
   */
  std::vector<const CheckpointChunk *> all() const;

  /**
   * Find checkpoint nearest to a specific time
   */
  std::optional<const CheckpointChunk *> nearestTo(uint32_t time_ms) const;

  /**
   * Get checkpoints within a time range (inclusive)
   */
  std::vector<const CheckpointChunk *> inTimeRange(uint32_t start_ms,
                                                    uint32_t end_ms) const;

  /**
   * Get total number of checkpoints
   */
  size_t count() const;

  /**
   * Iterator support for range-based for loops
   */
  using const_iterator = std::vector<const CheckpointChunk *>::const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

private:
  friend class Replay;
  explicit CheckpointStore(const Replay *replay);

  const Replay *m_replay;
  mutable std::vector<const CheckpointChunk *>
      m_cached_checkpoints; // Cached for iterator support
};

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_STORES_CHECKPOINT_STORE_HPP
