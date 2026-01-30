#include "fortnite_replay/parser.hpp"
#include "fortnite_replay.h"
#include <iostream>

namespace fortnite_replay
{

    FortniteReplayParser::FortniteReplayParser() = default;
    FortniteReplayParser::~FortniteReplayParser() = default;

    FortniteReplayParser::FortniteReplayParser(FortniteReplayParser &&) noexcept = default;
    FortniteReplayParser &FortniteReplayParser::operator=(FortniteReplayParser &&) noexcept = default;

    bool FortniteReplayParser::parse(const std::string &filepath)
    {
        m_replay.reset();
        m_stream.reset();
        m_file.reset();

        m_file = std::make_unique<std::ifstream>(filepath, std::ios::binary);
        if (!m_file->is_open())
        {
            return false;
        }

        try
        {
            m_stream = std::make_unique<kaitai::kstream>(m_file.get());
            m_replay = std::make_unique<fortnite_replay_t>(m_stream.get());
        }
        catch (const std::exception &e)
        {
            std::cerr << "Parse error: " << e.what() << std::endl;
            m_replay.reset();
            return false;
        }

        return true;
    }

    std::string FortniteReplayParser::magic() const
    {
        return m_replay ? m_replay->replay_info()->magic() : "";
    }

    uint32_t FortniteReplayParser::file_version() const
    {
        return m_replay ? m_replay->replay_info()->file_version() : -1;
    }

    uint32_t FortniteReplayParser::length_in_ms() const
    {
        return m_replay ? m_replay->replay_info()->length_in_ms() : 0;
    }

    uint32_t FortniteReplayParser::network_version() const
    {
        return m_replay ? m_replay->replay_info()->network_version() : 0;
    }

    uint32_t FortniteReplayParser::changelist() const
    {
        return m_replay ? m_replay->replay_info()->changelist() : 0;
    }

    std::string FortniteReplayParser::friendly_name() const
    {
        if (!m_replay || !m_replay->replay_info()->friendly_name())
        {
            return "";
        }
        if (m_replay->replay_info()->friendly_name()->value_ascii().size() > 0)
        {
            return m_replay->replay_info()->friendly_name()->value_ascii();
        }
        return m_replay->replay_info()->friendly_name()->value_unicode();
    }

    bool FortniteReplayParser::is_live() const
    {
        return m_replay ? (m_replay->replay_info()->is_live() != 0) : false;
    }

    uint64_t FortniteReplayParser::timestamp() const
    {
        return m_replay ? m_replay->replay_info()->timestamp() : 0;
    }

    bool FortniteReplayParser::is_compressed() const
    {
        return m_replay ? (m_replay->replay_info()->is_compressed() != 0) : false;
    }

} // namespace fortnite_replay
