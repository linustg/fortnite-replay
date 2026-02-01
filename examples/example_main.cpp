#include <iostream>
#include <iomanip>
#include <string>
#include "fortnite_replay/parser.hpp"
#include "fortnite_replay/replay.hpp"
#include "fortnite_replay/utils.hpp"

using namespace fortnite_replay;

// Helper function to format time in seconds
std::string format_time(uint32_t time_ms)
{
    uint32_t seconds = time_ms / 1000;
    uint32_t minutes = seconds / 60;
    uint32_t remaining_seconds = seconds % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << remaining_seconds;
    return oss.str();
}

// Helper function to format bytes
std::string format_bytes(size_t bytes)
{
    const char* units[] = {"B", "KB", "MB", "GB"};
    int unit_index = 0;
    double size = static_cast<double>(bytes);

    while (size >= 1024.0 && unit_index < 3)
    {
        size /= 1024.0;
        unit_index++;
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << size << " " << units[unit_index];
    return oss.str();
}

void print_separator(const std::string& title = "")
{
    std::cout << "\n";
    if (title.empty())
    {
        std::cout << std::string(80, '=') << "\n";
    }
    else
    {
        std::cout << "=== " << title << " ";
        std::cout << std::string(76 - title.length(), '=') << "\n";
    }
}

void print_replay_info(const Replay& replay)
{
    print_separator("REPLAY INFORMATION");

    const auto& info = replay.info();

    std::cout << "  Friendly Name: " << info.friendly_name << "\n";
    std::cout << "  Duration: " << format_time(info.length_ms)
              << " (" << info.length_ms << " ms)\n";
    std::cout << "  File Version: " << info.file_version << "\n";
    std::cout << "  Network Version: " << info.network_version << "\n";
    std::cout << "  Changelist: " << info.changelist << "\n";
    std::cout << "  Is Live: " << (info.is_live ? "Yes" : "No") << "\n";
    std::cout << "  Is Compressed: " << (info.is_compressed ? "Yes" : "No") << "\n";
    std::cout << "  Is Encrypted: " << (info.is_encrypted ? "Yes" : "No") << "\n";

    if (info.timestamp.has_value())
    {
        std::cout << "  Timestamp: " << info.timestamp.value() << "\n";
    }

    if (!info.custom_versions.empty())
    {
        std::cout << "  Custom Versions: " << info.custom_versions.size() << "\n";
    }
}

void print_header_info(const Replay& replay)
{
    auto* header = replay.header().get();
    if (!header)
    {
        return;
    }

    print_separator("HEADER INFORMATION");

    std::cout << "  Network Version: " << header->network_version << "\n";
    std::cout << "  Network Checksum: " << header->network_checksum << "\n";
    std::cout << "  Engine Network Version: " << header->engine_network_version << "\n";
    std::cout << "  Game Network Protocol Version: " << header->game_network_protocol_version << "\n";

    if (header->engine_version.has_value())
    {
        const auto& version = header->engine_version.value();
        std::cout << "  Engine Version: " << version.to_string()
                  << " (Changelist: " << version.changelist << ")\n";
        if (!version.branch.empty())
        {
            std::cout << "  Engine Branch: " << version.branch << "\n";
        }
    }

    if (!header->levels.empty())
    {
        std::cout << "\n  Levels:\n";
        for (const auto& level : header->levels)
        {
            std::cout << "    - " << level.name << " @ " << format_time(level.time_ms) << "\n";
        }
    }

    // Print flags
    std::cout << "\n  Replay Flags:\n";
    std::cout << "    Client Recorded: " << (header->flags.client_recorded ? "Yes" : "No") << "\n";
    std::cout << "    Has Streaming Fixes: " << (header->flags.has_streaming_fixes ? "Yes" : "No") << "\n";
    std::cout << "    Delta Checkpoints: " << (header->flags.delta_checkpoints ? "Yes" : "No") << "\n";
    std::cout << "    Game Specific Frame Data: " << (header->flags.game_specific_frame_data ? "Yes" : "No") << "\n";
    std::cout << "    Replay Connection: " << (header->flags.replay_connection ? "Yes" : "No") << "\n";
    std::cout << "    Actor Prioritization: " << (header->flags.actor_prioritization_enabled ? "Yes" : "No") << "\n";
    std::cout << "    Net Relevancy: " << (header->flags.net_relevancy_enabled ? "Yes" : "No") << "\n";
    std::cout << "    Async Recorded: " << (header->flags.async_recorded ? "Yes" : "No") << "\n";

    if (header->package_version_info.has_value())
    {
        const auto& pkg = header->package_version_info.value();
        std::cout << "\n  Package Version Info:\n";
        std::cout << "    Platform: " << pkg.platform << "\n";
        std::cout << "    Min Record Hz: " << pkg.min_record_hz << "\n";
        std::cout << "    Max Record Hz: " << pkg.max_record_hz << "\n";
        std::cout << "    Frame Limit: " << pkg.frame_limit_ms << " ms\n";
        std::cout << "    Checkpoint Limit: " << pkg.checkpoint_limit_ms << " ms\n";
    }
}

void print_statistics(const Replay& replay)
{
    print_separator("STATISTICS");

    std::cout << "  Total Chunks: " << replay.chunk_count() << "\n";
    std::cout << "  Data Frames: " << replay.frame_count() << "\n";
    std::cout << "  Checkpoints: " << replay.checkpoint_count() << "\n";
    std::cout << "  Events: " << replay.event_count() << "\n";
}

void print_data_frames_summary(const Replay& replay)
{
    auto data_chunks = replay.data().all();
    if (data_chunks.empty())
    {
        return;
    }

    print_separator("DATA FRAMES SUMMARY");

    // Calculate statistics
    size_t total_data_size = 0;
    size_t total_memory_size = 0;
    uint32_t min_time = UINT32_MAX;
    uint32_t max_time = 0;

    for (const auto* frame : data_chunks)
    {
        total_data_size += frame->data_length;
        total_memory_size += frame->memory_size_bytes;
        min_time = std::min(min_time, frame->start_time_ms);
        max_time = std::max(max_time, frame->end_time_ms);
    }

    std::cout << "  Total Frames: " << data_chunks.size() << "\n";
    std::cout << "  Time Range: " << format_time(min_time) << " - " << format_time(max_time) << "\n";
    std::cout << "  Total Data Size: " << format_bytes(total_data_size) << "\n";
    std::cout << "  Total Memory Size: " << format_bytes(total_memory_size) << "\n";

    // Show first few frames as samples
    std::cout << "\n  Sample Frames (first 5):\n";
    for (size_t i = 0; i < std::min(size_t(5), data_chunks.size()); ++i)
    {
        const auto* frame = data_chunks[i];
        std::cout << "    Frame " << (i + 1) << ": "
                  << format_time(frame->start_time_ms) << " - " << format_time(frame->end_time_ms)
                  << " (" << frame->duration_ms() << " ms, "
                  << format_bytes(frame->data_length) << ")\n";
    }
}

void print_checkpoints(const Replay& replay)
{
    auto checkpoints = replay.checkpoints().all();
    if (checkpoints.empty())
    {
        return;
    }

    print_separator("CHECKPOINTS");

    std::cout << "  Total Checkpoints: " << checkpoints.size() << "\n\n";

    for (size_t i = 0; i < checkpoints.size(); ++i)
    {
        const auto* cp = checkpoints[i];
        std::cout << "  Checkpoint " << (i + 1) << ":\n";
        std::cout << "    ID: " << cp->id << "\n";
        std::cout << "    Group: " << cp->group << "\n";
        if (!cp->metadata.empty())
        {
            std::cout << "    Metadata: " << cp->metadata << "\n";
        }
        std::cout << "    Time: " << format_time(cp->start_time_ms) << "\n";
        std::cout << "    Data Size: " << format_bytes(cp->data.size()) << "\n";
        std::cout << "\n";
    }
}

void print_events(const Replay& replay)
{
    auto events = replay.events().all();
    if (events.empty())
    {
        return;
    }

    print_separator("EVENTS");

    std::cout << "  Total Events: " << events.size() << "\n\n";

    for (size_t i = 0; i < events.size(); ++i)
    {
        const auto* event = events[i];
        std::cout << "  Event " << (i + 1) << ":\n";
        std::cout << "    ID: " << event->id << "\n";
        std::cout << "    Event Type: " << Utils::event_type_to_string(event->event_type) << "\n";
        if (!event->metadata.empty())
        {
            std::cout << "    Metadata: " << event->metadata << "\n";
        }
        std::cout << "    Time: " << format_time(event->start_time_ms);
        if (event->duration_ms() > 0)
        {
            std::cout << " - " << format_time(event->end_time_ms)
                      << " (duration: " << event->duration_ms() << " ms)";
        }
        std::cout << "\n";
        std::cout << "    Data Size: " << format_bytes(event->data.size()) << "\n";
        std::cout << "\n";
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <replay_file.replay>\n";
        std::cerr << "\nExample:\n";
        std::cerr << "  " << argv[0] << " my_replay.replay\n";
        return 1;
    }

    std::string replay_path = argv[1];

    std::cout << "Parsing Fortnite replay: " << replay_path << "\n";

    // Create parser and parse the replay file
    FortniteReplayParser parser;
    if (!parser.parse(replay_path))
    {
        std::cerr << "Error: Failed to parse replay file.\n";
        std::cerr << "Make sure the file exists and is a valid Fortnite replay.\n";
        return 1;
    }

    // Get the parsed replay object
    Replay replay = parser.replay();

    // Display all information in structured format
    print_replay_info(replay);
    print_header_info(replay);
    print_statistics(replay);
    print_data_frames_summary(replay);
    print_checkpoints(replay);
    print_events(replay);

    print_separator();
    std::cout << "\nParsing completed successfully!\n";

    return 0;
}
