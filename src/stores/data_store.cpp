#include "fortnite_replay/stores/data_store.hpp"
#include "fortnite_replay/replay.hpp"
#include <algorithm>

namespace fortnite_replay {

DataStore::DataStore(const Replay *replay) : m_replay(replay) {}

std::vector<const DataChunk *> DataStore::all() const {
  auto chunks = m_replay->chunks_of_type<DataChunk>();
  std::vector<const DataChunk *> result;
  result.reserve(chunks.size());
  for (auto *chunk : chunks) {
    result.push_back(chunk);
  }
  return result;
}

std::optional<const DataChunk *> DataStore::frameAtTime(uint32_t time_ms) const {
  auto chunks = all();
  auto it = std::find_if(chunks.begin(), chunks.end(),
                         [time_ms](const DataChunk *chunk) {
                           return time_ms >= chunk->start_time_ms &&
                                  time_ms <= chunk->end_time_ms;
                         });
  if (it != chunks.end()) {
    return *it;
  }
  return std::nullopt;
}

std::vector<const DataChunk *> DataStore::framesInRange(uint32_t start_ms,
                                                         uint32_t end_ms) const {
  auto chunks = all();
  std::vector<const DataChunk *> result;
  std::copy_if(
      chunks.begin(), chunks.end(), std::back_inserter(result),
      [start_ms, end_ms](const DataChunk *chunk) {
        return chunk->start_time_ms <= end_ms && chunk->end_time_ms >= start_ms;
      });
  return result;
}

size_t DataStore::count() const {
  return m_replay->chunks_of_type<DataChunk>().size();
}

uint32_t DataStore::totalDuration() const {
  auto chunks = all();
  uint32_t total = 0;
  for (const auto *chunk : chunks) {
    total += chunk->duration_ms();
  }
  return total;
}

DataStore::const_iterator DataStore::begin() const {
  if (m_cached_chunks.empty()) {
    m_cached_chunks = all();
  }
  return m_cached_chunks.begin();
}

DataStore::const_iterator DataStore::end() const {
  if (m_cached_chunks.empty()) {
    m_cached_chunks = all();
  }
  return m_cached_chunks.end();
}

} // namespace fortnite_replay
