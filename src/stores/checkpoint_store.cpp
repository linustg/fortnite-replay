#include "fortnite_replay/stores/checkpoint_store.hpp"
#include "fortnite_replay/replay.hpp"
#include <algorithm>
#include <cstdlib>
#include <limits>

namespace fortnite_replay {

CheckpointStore::CheckpointStore(const Replay *replay) : m_replay(replay) {}

std::vector<const CheckpointChunk *> CheckpointStore::all() const {
  auto checkpoints = m_replay->chunks_of_type<CheckpointChunk>();
  std::vector<const CheckpointChunk *> result;
  result.reserve(checkpoints.size());
  for (auto *checkpoint : checkpoints) {
    result.push_back(checkpoint);
  }
  return result;
}

std::optional<const CheckpointChunk *>
CheckpointStore::nearestTo(uint32_t time_ms) const {
  auto checkpoints = all();
  if (checkpoints.empty()) {
    return std::nullopt;
  }

  const CheckpointChunk *nearest = nullptr;
  uint32_t min_distance = std::numeric_limits<uint32_t>::max();

  for (const auto *checkpoint : checkpoints) {
    // Calculate distance from checkpoint start time
    uint32_t distance = (time_ms > checkpoint->start_time_ms)
                            ? (time_ms - checkpoint->start_time_ms)
                            : (checkpoint->start_time_ms - time_ms);

    if (distance < min_distance) {
      min_distance = distance;
      nearest = checkpoint;
    }
  }

  return nearest;
}

std::vector<const CheckpointChunk *>
CheckpointStore::inTimeRange(uint32_t start_ms, uint32_t end_ms) const {
  auto checkpoints = all();
  std::vector<const CheckpointChunk *> result;
  std::copy_if(checkpoints.begin(), checkpoints.end(),
               std::back_inserter(result),
               [start_ms, end_ms](const CheckpointChunk *checkpoint) {
                 return checkpoint->start_time_ms <= end_ms &&
                        checkpoint->end_time_ms >= start_ms;
               });
  return result;
}

size_t CheckpointStore::count() const {
  return m_replay->chunks_of_type<CheckpointChunk>().size();
}

CheckpointStore::const_iterator CheckpointStore::begin() const {
  if (m_cached_checkpoints.empty()) {
    m_cached_checkpoints = all();
  }
  return m_cached_checkpoints.begin();
}

CheckpointStore::const_iterator CheckpointStore::end() const {
  if (m_cached_checkpoints.empty()) {
    m_cached_checkpoints = all();
  }
  return m_cached_checkpoints.end();
}

} // namespace fortnite_replay
