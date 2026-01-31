#ifndef FORTNITE_REPLAY_PARSER_HPP
#define FORTNITE_REPLAY_PARSER_HPP

#include <memory>
#include <string>
#include <cstdint>
#include <fstream>

#include "kaitai/kaitaistruct.h"
#include "kaitai/kaitaistream.h"
#include "fortnite_replay/replay.hpp"

class fortnite_replay_t;

namespace fortnite_replay
{

    class FortniteReplayParser
    {
    public:
        FortniteReplayParser();
        ~FortniteReplayParser();

        FortniteReplayParser(const FortniteReplayParser &) = delete;
        FortniteReplayParser &operator=(const FortniteReplayParser &) = delete;
        FortniteReplayParser(FortniteReplayParser &&) noexcept;
        FortniteReplayParser &operator=(FortniteReplayParser &&) noexcept;

        bool parse(const std::string &filepath);

        // Info header
        std::string magic() const;
        uint32_t file_version() const;
        uint32_t length_in_ms() const;
        uint32_t network_version() const;
        uint32_t changelist() const;
        std::string friendly_name() const;
        bool is_live() const;
        uint64_t timestamp() const;
        bool is_compressed() const;

        // Get the parsed replay as a well-formatted model
        Replay replay();

        bool is_valid() const { return m_replay != nullptr; }

    private:
        std::unique_ptr<std::ifstream> m_file;
        std::unique_ptr<kaitai::kstream> m_stream;
        std::unique_ptr<fortnite_replay_t> m_replay;
    };

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_PARSER_HPP
