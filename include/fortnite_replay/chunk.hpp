#ifndef FORTNITE_REPLAY_CHUNK_HPP
#define FORTNITE_REPLAY_CHUNK_HPP

#include "chunk_type.hpp"

namespace fortnite_replay
{

    /**
     * Abstract base class for all replay chunks
     */
    class Chunk
    {
    public:
        virtual ~Chunk() = default;

        /**
         * Get the type of this chunk
         */
        virtual ChunkType type() const = 0;

        /**
         * Get the type name as a string
         */
        virtual const char *type_name() const = 0;

    protected:
        Chunk() = default;
        Chunk(const Chunk &) = default;
        Chunk(Chunk &&) = default;
        Chunk &operator=(const Chunk &) = default;
        Chunk &operator=(Chunk &&) = default;
    };

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_CHUNK_HPP
