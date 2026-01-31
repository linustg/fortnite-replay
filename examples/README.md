# Fortnite Replay Viewer Example

This example demonstrates how to parse and display Fortnite replay files using the fortnite_replay library.

## Building

The example is built automatically when you build the project:

```bash
./build.sh
```

The executable will be created at: `build/bin/replay_viewer`

## Usage

Run the replay viewer with a replay file:

```bash
./build/bin/replay_viewer path/to/your_replay.replay
```

## Example Output

The viewer displays the replay information in a structured format:

```
=== REPLAY INFORMATION ===========================================
  Friendly Name: Victory Royale!
  Duration: 23:45 (1425000 ms)
  File Version: 7
  Network Version: 19
  Changelist: 12345678
  Is Live: No
  Is Compressed: Yes
  Is Encrypted: No

=== HEADER INFORMATION ===========================================
  Network Version: 19
  Network Checksum: 1234567890
  Engine Network Version: 27
  Engine Version: 5.4.1 (Changelist: 12345678)

  Levels:
    - /Game/Athena/Maps/Athena_Terrain @ 00:00

  Replay Flags:
    Client Recorded: Yes
    Has Streaming Fixes: Yes
    Delta Checkpoints: Yes
    ...

=== STATISTICS ===================================================
  Total Chunks: 1523
  Data Frames: 1500
  Checkpoints: 20
  Events: 3

=== DATA FRAMES SUMMARY ==========================================
  Total Frames: 1500
  Time Range: 00:00 - 23:45
  Total Data Size: 45.23 MB
  Total Memory Size: 120.45 MB

  Sample Frames (first 5):
    Frame 1: 00:00 - 00:01 (1000 ms, 30.12 KB)
    Frame 2: 00:01 - 00:02 (1000 ms, 29.87 KB)
    ...

=== CHECKPOINTS ==================================================
  Total Checkpoints: 20

  Checkpoint 1:
    ID: checkpoint_0
    Group: PlayerState
    Time: 01:00
    Data Size: 2.34 KB

=== EVENTS =======================================================
  Total Events: 3

  Event 1:
    ID: kill_1
    Group: playerElim
    Metadata: HeadShot
    Time: 15:32
    Data Size: 512 B
```

## Features Demonstrated

The example shows how to:

- Parse a Fortnite replay file using `FortniteReplayParser`
- Access the `Replay` object with all parsed data
- Display replay metadata (friendly name, duration, versions, etc.)
- Access header information (network versions, engine version, levels, flags)
- Get statistics about chunks (total counts, frame counts, etc.)
- Iterate through data frames with timing and size information
- Access checkpoints with IDs, groups, and metadata
- Display events with timing and associated data
- Format time values (milliseconds to MM:SS)
- Format byte sizes (B, KB, MB, GB)

## Code Structure

The example includes several helper functions:

- `format_time()` - Converts milliseconds to MM:SS format
- `format_bytes()` - Formats byte sizes with appropriate units
- `print_replay_info()` - Displays replay metadata
- `print_header_info()` - Shows header and version information
- `print_statistics()` - Displays chunk statistics
- `print_data_frames_summary()` - Shows frame data summary
- `print_checkpoints()` - Lists all checkpoints
- `print_events()` - Lists all events

## Integration in Your Code

You can use this example as a template for integrating replay parsing into your own application:

```cpp
#include "fortnite_replay/parser.hpp"
#include "fortnite_replay/replay.hpp"

using namespace fortnite_replay;

// Parse the replay
FortniteReplayParser parser;
if (parser.parse("my_replay.replay")) {
    Replay replay = parser.replay();

    // Access replay info
    std::cout << "Name: " << replay.friendly_name() << "\n";
    std::cout << "Duration: " << replay.duration().count() << " ms\n";

    // Access header
    if (auto* header = replay.header_chunk()) {
        std::cout << "Network Version: " << header->network_version << "\n";
    }

    // Access frames
    for (auto* frame : replay.data_chunks()) {
        // Process frame data
    }

    // Access events
    for (auto* event : replay.event_chunks()) {
        std::cout << "Event: " << event->id << " @ " << event->start_time_ms << "\n";
    }
}
```
