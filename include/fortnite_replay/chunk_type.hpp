#ifndef FORTNITE_REPLAY_CHUNK_TYPE_HPP
#define FORTNITE_REPLAY_CHUNK_TYPE_HPP

#include <cstdint>

namespace fortnite_replay
{

    /**
     * Type of replay chunk
     */
    enum class ChunkType : uint32_t
    {
        Header = 0,
        ReplayData = 1,
        Checkpoint = 2,
        Event = 3,
        Unknown = 0xFFFFFFFF
    };

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_CHUNK_TYPE_HPP
