#include "fortnite_replay/replay.hpp"

namespace fortnite_replay {

// Private method used by HeaderStore
HeaderChunk *Replay::header_chunk() const {
  for (const auto &chunk : m_chunks) {
    if (auto *h = dynamic_cast<HeaderChunk *>(chunk.get()))
      return h;
  }
  return nullptr;
}

} // namespace fortnite_replay
