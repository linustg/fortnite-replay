#include "fortnite_replay/replay.hpp"

namespace fortnite_replay {

HeaderChunk *Replay::header_chunk() const {
  for (const auto &chunk : m_chunks) {
    if (auto *h = dynamic_cast<HeaderChunk *>(chunk.get()))
      return h;
  }
  return nullptr;
}

std::vector<DataChunk *> Replay::data_chunks() const {
  return chunks_of_type<DataChunk>();
}

std::vector<CheckpointChunk *> Replay::checkpoint_chunks() const {
  return chunks_of_type<CheckpointChunk>();
}

std::vector<Event *> Replay::event_chunks() const {
  return chunks_of_type<Event>();
}

std::optional<HeaderChunk> Replay::header() const {
  if (auto *h = header_chunk())
    return *h;
  return std::nullopt;
}

std::vector<DataChunk> Replay::data_frames() const {
  std::vector<DataChunk> result;
  for (auto *chunk : data_chunks())
    result.push_back(*chunk);
  return result;
}

std::vector<CheckpointChunk> Replay::checkpoints() const {
  std::vector<CheckpointChunk> result;
  for (auto *chunk : checkpoint_chunks())
    result.push_back(*chunk);
  return result;
}

std::vector<Event> Replay::events() const {
  std::vector<Event> result;
  for (auto *chunk : event_chunks())
    result.push_back(*chunk);
  return result;
}

} // namespace fortnite_replay
