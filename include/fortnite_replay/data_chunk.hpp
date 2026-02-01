#ifndef FORTNITE_REPLAY_DATA_CHUNK_HPP
#define FORTNITE_REPLAY_DATA_CHUNK_HPP

#include "chunk.hpp"
#include "chunk_type.hpp"

#include <cstdint>
#include <vector>

namespace fortnite_replay {

/**
 * Data chunk containing recorded network frames
 */
class DataChunk : public Chunk {
public:
  DataChunk() = default;

  ChunkType type() const override { return ChunkType::ReplayData; }
  const char *type_name() const override { return "ReplayData"; }

  uint32_t start_time_ms = 0;
  uint32_t end_time_ms = 0;
  uint32_t data_length = 0;
  int32_t memory_size_bytes = 0;
  std::vector<uint8_t> data; // Raw frame data (may be compressed/encrypted)

  /**
   * Get duration of this data chunk in milliseconds
   */
  uint32_t duration_ms() const {
    return end_time_ms > start_time_ms ? end_time_ms - start_time_ms : 0;
  }
};

// Type alias for backward compatibility
using ReplayDataFrame = DataChunk;

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_DATA_CHUNK_HPP
