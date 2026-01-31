#ifndef FORTNITE_REPLAY_REPLAY_HPP
#define FORTNITE_REPLAY_REPLAY_HPP

// Convenience header that includes all replay components

// Standard library
#include <chrono>

// Enums
#include "chunk_type.hpp"

// Chunk classes
#include "chunk.hpp"
#include "checkpoint_chunk.hpp"
#include "data_chunk.hpp"
#include "event_chunk.hpp"
#include "header_chunk.hpp"

namespace fortnite_replay
{

    /**
     * Replay file metadata (from replay_info header)
     */
    struct ReplayInfo
    {
        uint32_t file_version = 0;
        uint32_t length_ms = 0;
        uint32_t network_version = 0;
        uint32_t changelist = 0;
        std::string friendly_name;
        bool is_live = false;
        std::optional<int64_t> timestamp; // .NET DateTime binary format
        bool is_compressed = false;
        bool is_encrypted = false;
        std::vector<uint8_t> encryption_key;
        std::vector<CustomVersion> custom_versions;

        /**
         * Get duration as std::chrono::milliseconds
         */
        std::chrono::milliseconds duration() const
        {
            return std::chrono::milliseconds(length_ms);
        }
    };

    /**
     * Main Replay class holding all parsed replay data
     */
    class Replay
    {
    public:
        Replay() = default;

        // ====================================================================
        // Chunk access
        // ====================================================================

        /**
         * Get all chunks in the replay
         */
        const std::vector<std::unique_ptr<Chunk>> &chunks() const { return m_chunks; }
        std::vector<std::unique_ptr<Chunk>> &chunks() { return m_chunks; }

        /**
         * Add a chunk to the replay
         */
        template <typename T, typename... Args>
        T &add_chunk(Args &&...args)
        {
            auto chunk = std::make_unique<T>(std::forward<Args>(args)...);
            T &ref = *chunk;
            m_chunks.push_back(std::move(chunk));
            return ref;
        }

        /**
         * Get chunks of a specific type
         */
        template <typename T>
        std::vector<T *> chunks_of_type() const
        {
            std::vector<T *> result;
            for (const auto &chunk : m_chunks)
            {
                if (auto *typed = dynamic_cast<T *>(chunk.get()))
                {
                    result.push_back(typed);
                }
            }
            return result;
        }

        // ====================================================================
        // Typed chunk accessors (convenience methods)
        // ====================================================================

        /**
         * Get the header chunk (first one found, or nullptr)
         */
        HeaderChunk *header_chunk() const;

        /**
         * Get all data chunks
         */
        std::vector<DataChunk *> data_chunks() const;

        /**
         * Get all checkpoint chunks
         */
        std::vector<CheckpointChunk *> checkpoint_chunks() const;

        /**
         * Get all event chunks
         */
        std::vector<EventChunk *> event_chunks() const;

        // ====================================================================
        // ReplayInfo accessors
        // ====================================================================

        const ReplayInfo &info() const { return m_info; }
        ReplayInfo &info() { return m_info; }

        // ====================================================================
        // Backward-compatible accessors
        // ====================================================================

        /**
         * @deprecated Use header_chunk() instead
         */
        std::optional<HeaderChunk> header() const;

        /**
         * @deprecated Use data_chunks() instead
         */
        std::vector<DataChunk> data_frames() const;

        /**
         * @deprecated Use checkpoint_chunks() instead
         */
        std::vector<CheckpointChunk> checkpoints() const;

        /**
         * @deprecated Use event_chunks() instead
         */
        std::vector<EventChunk> events() const;

        // ====================================================================
        // Convenience accessors
        // ====================================================================

        std::string friendly_name() const { return m_info.friendly_name; }
        std::chrono::milliseconds duration() const { return m_info.duration(); }
        bool is_compressed() const { return m_info.is_compressed; }
        bool is_encrypted() const { return m_info.is_encrypted; }
        bool is_live() const { return m_info.is_live; }

        // ====================================================================
        // Statistics
        // ====================================================================

        size_t chunk_count() const { return m_chunks.size(); }
        size_t frame_count() const { return data_chunks().size(); }
        size_t checkpoint_count() const { return checkpoint_chunks().size(); }
        size_t event_count() const { return event_chunks().size(); }

    private:
        ReplayInfo m_info;
        std::vector<std::unique_ptr<Chunk>> m_chunks;
    };

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_REPLAY_HPP
