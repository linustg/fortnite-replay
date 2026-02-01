#ifndef FORTNITE_REPLAY_CHECKPOINT_CHUNK_HPP
#define FORTNITE_REPLAY_CHECKPOINT_CHUNK_HPP

#include "chunk.hpp"
#include "chunk_type.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace fortnite_replay {

/**
 * Checkpoint chunk for fast-forwarding through replay
 */
class CheckpointChunk : public Chunk {
public:
  CheckpointChunk() = default;

  ChunkType type() const override { return ChunkType::Checkpoint; }
  const char *type_name() const override { return "Checkpoint"; }

  std::string id;
  std::string group;
  std::string metadata;
  uint32_t start_time_ms = 0;
  uint32_t end_time_ms = 0;
  std::vector<uint8_t>
      data; // Raw checkpoint data (may be encrypted/compressed)

  /**
   * Get duration of this checkpoint in milliseconds
   */
  uint32_t duration_ms() const {
    return end_time_ms > start_time_ms ? end_time_ms - start_time_ms : 0;
  }
};

// Type alias for backward compatibility
using Checkpoint = CheckpointChunk;

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_CHECKPOINT_CHUNK_HPP
