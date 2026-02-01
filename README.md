# Fortnite Replay Parser

[![CI](https://github.com/linustg/fortnite-replay/actions/workflows/ci.yml/badge.svg)](https://github.com/linustg/fortnite-replay/actions/workflows/ci.yml)
[![License](https://img.shields.io/github/license/linustg/fortnite-replay)](LICENSE)
[![codecov](https://codecov.io/gh/linustg/fortnite-replay/branch/main/graph/badge.svg)](https://codecov.io/gh/linustg/fortnite-replay)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey)](https://github.com/linustg/fortnite-replay)

A modern C++23 library for parsing Fortnite replay files (`.replay`). This library provides a clean, type-safe API to extract and analyze replay data including metadata, network frames, checkpoints, and game events.

## Features

- **Full Replay Parsing** - Parse complete Fortnite replay files
- **Type-Safe API** - Modern C++23 with strong typing
- **Comprehensive Data Access** - Access all replay components:
  - Replay metadata (version, duration, network info)
  - Header information (engine version, network checksums, flags)
  - Data chunks (network replay frames)
  - Checkpoints (for fast-forwarding)
  - Events (kills, stats, game-specific events)
- **Cross-Platform** - Works on Linux, macOS, and Windows
- **Zero Dependencies** (except Kaitai Struct runtime, fetched automatically)
- **Tested** - Comprehensive unit tests with Google Test

## Quick Start

### Prerequisites

- C++23 compatible compiler (GCC 11+, Clang 14+, MSVC 2022+)
- CMake 3.25 or higher (required for C++23 support)
- OpenSSL (for AES decryption)
- zlib (for compression support)
- Google Test (for running tests)
- **oo2core library** (optional, for Oodle decompression support)
  - Required for decompressing Oodle-compressed replay data
  - Proprietary library not included in this repository
  - Must be available on your system for full functionality
  - Tests requiring oo2core are automatically skipped in CI environments

### Building

```bash
# Clone the repository
git clone https://github.com/linustg/fortnite-replay.git
cd fortnite-replay

# Build the project
./build.sh

# Or manually with CMake
cmake -B build -S .
cmake --build build

# Run tests
cd build
ctest --output-on-failure
```

### Installation

```bash
# Build and install
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build build
sudo cmake --install build
```

## Usage

### Basic Example

```cpp
#include <iostream>
#include "fortnite_replay/parser.hpp"
#include "fortnite_replay/replay.hpp"

using namespace fortnite_replay;

int main() {
    // Create parser and parse replay file
    FortniteReplayParser parser;
    if (!parser.parse("my_replay.replay")) {
        std::cerr << "Failed to parse replay\n";
        return 1;
    }

    // Get the parsed replay object
    Replay replay = parser.replay();

    // Access replay information
    std::cout << "Replay Name: " << replay.friendly_name() << "\n";
    std::cout << "Duration: " << replay.duration().count() << " ms\n";
    std::cout << "Network Version: " << replay.info().network_version << "\n";
    std::cout << "Total Chunks: " << replay.chunk_count() << "\n";

    return 0;
}
```

### Accessing Header Information

```cpp
// Get header chunk
if (auto* header = replay.header_chunk()) {
    std::cout << "Network Version: " << header->network_version << "\n";
    std::cout << "Network Checksum: " << header->network_checksum << "\n";

    // Engine version
    if (header->engine_version.has_value()) {
        auto& version = header->engine_version.value();
        std::cout << "Engine: " << version.to_string() << "\n";
        std::cout << "Branch: " << version.branch << "\n";
    }

    // Replay flags
    std::cout << "Client Recorded: "
              << (header->flags.client_recorded ? "Yes" : "No") << "\n";
    std::cout << "Has Streaming Fixes: "
              << (header->flags.has_streaming_fixes ? "Yes" : "No") << "\n";
}
```

### Processing Data Frames

```cpp
// Get all data frames
auto frames = replay.data_chunks();
std::cout << "Total frames: " << frames.size() << "\n";

for (const auto* frame : frames) {
    std::cout << "Frame: " << frame->start_time_ms << " - "
              << frame->end_time_ms << " ms\n";
    std::cout << "  Duration: " << frame->duration_ms() << " ms\n";
    std::cout << "  Data size: " << frame->data_length << " bytes\n";
    std::cout << "  Memory size: " << frame->memory_size_bytes << " bytes\n";
}
```

### Processing Events

```cpp
// Get all events
auto events = replay.event_chunks();
std::cout << "Total events: " << events.size() << "\n";

for (const auto* event : events) {
    std::cout << "Event: " << event->id << "\n";
    std::cout << "  Group: " << event->group << "\n";
    std::cout << "  Time: " << event->start_time_ms << " ms\n";

    // Check for specific event types
    if (event->group == "playerElim") {
        std::cout << "  Player elimination at " << event->start_time_ms << " ms\n";
    }
}
```

### Processing Checkpoints

```cpp
// Get all checkpoints
auto checkpoints = replay.checkpoint_chunks();
std::cout << "Total checkpoints: " << checkpoints.size() << "\n";

for (const auto* cp : checkpoints) {
    std::cout << "Checkpoint: " << cp->id << "\n";
    std::cout << "  Group: " << cp->group << "\n";
    std::cout << "  Time: " << cp->start_time_ms << " ms\n";
    std::cout << "  Data size: " << cp->data.size() << " bytes\n";
}
```

## Comprehensive Example

A complete example program is available in `examples/example_main.cpp`. Build and run it:

```bash
# Build the example
./build.sh

# Run the replay viewer
./build/bin/replay_viewer path/to/replay.replay
```

This will display:
- Complete replay metadata
- Header information with engine version and flags
- Statistics (chunk counts, frame counts, etc.)
- Data frames summary with timing and size information
- All checkpoints with IDs and metadata
- All events with groups and timing

See [examples/README.md](examples/README.md) for detailed documentation.

## API Reference

### Main Classes

#### `FortniteReplayParser`

The main parser class for reading replay files.

```cpp
class FortniteReplayParser {
public:
    bool parse(const std::string& filepath);
    Replay replay();
    bool is_valid() const;

    // Direct accessors (legacy)
    std::string magic() const;
    uint32_t file_version() const;
    uint32_t length_in_ms() const;
    std::string friendly_name() const;
    // ... and more
};
```

#### `Replay`

The main replay data container.

```cpp
class Replay {
public:
    // Info accessors
    const ReplayInfo& info() const;
    std::string friendly_name() const;
    std::chrono::milliseconds duration() const;
    bool is_compressed() const;
    bool is_encrypted() const;

    // Chunk accessors
    HeaderChunk* header_chunk() const;
    std::vector<DataChunk*> data_chunks() const;
    std::vector<CheckpointChunk*> checkpoint_chunks() const;
    std::vector<Event*> event_chunks() const;

    // Statistics
    size_t chunk_count() const;
    size_t frame_count() const;
    size_t checkpoint_count() const;
    size_t event_count() const;
};
```

#### `ReplayInfo`

Replay metadata structure.

```cpp
struct ReplayInfo {
    uint32_t file_version;
    uint32_t length_ms;
    uint32_t network_version;
    uint32_t changelist;
    std::string friendly_name;
    bool is_live;
    std::optional<int64_t> timestamp;
    bool is_compressed;
    bool is_encrypted;
    std::vector<uint8_t> encryption_key;
    std::vector<CustomVersion> custom_versions;

    std::chrono::milliseconds duration() const;
};
```

#### Chunk Types

All chunk types inherit from the base `Chunk` class:

```cpp
// Base chunk class
class Chunk {
public:
    virtual ChunkType type() const = 0;
    virtual const char* type_name() const = 0;
};

// Header chunk
class HeaderChunk : public Chunk {
public:
    uint32_t network_version;
    uint32_t network_checksum;
    uint32_t engine_network_version;
    std::optional<EngineVersion> engine_version;
    std::vector<LevelInfo> levels;
    ReplayHeaderFlags flags;
    // ... and more
};

// Data chunk (network frames)
class DataChunk : public Chunk {
public:
    uint32_t start_time_ms;
    uint32_t end_time_ms;
    uint32_t data_length;
    int32_t memory_size_bytes;
    std::vector<uint8_t> data;

    uint32_t duration_ms() const;
};

// Checkpoint chunk
class CheckpointChunk : public Chunk {
public:
    std::string id;
    std::string group;
    std::string metadata;
    uint32_t start_time_ms;
    uint32_t end_time_ms;
    std::vector<uint8_t> data;

    uint32_t duration_ms() const;
};

// Event chunk
class Event : public Chunk {
public:
    std::string id;
    std::string group;
    std::string metadata;
    uint32_t start_time_ms;
    uint32_t end_time_ms;
    std::vector<uint8_t> data;

    uint32_t duration_ms() const;
};
```

### Supporting Structures

```cpp
// Engine version
struct EngineVersion {
    uint16_t major, minor, patch;
    uint32_t changelist;
    std::string branch;
    std::string to_string() const;
};

// Replay header flags
struct ReplayHeaderFlags {
    bool client_recorded;
    bool has_streaming_fixes;
    bool delta_checkpoints;
    bool game_specific_frame_data;
    bool replay_connection;
    bool actor_prioritization_enabled;
    bool net_relevancy_enabled;
    bool async_recorded;
};

// Level information
struct LevelInfo {
    std::string name;
    uint32_t time_ms;
};

// Custom version
struct CustomVersion {
    std::string guid;
    int32_t version;
};
```

## Project Structure

```
fortnite-replay/
├── include/fortnite_replay/   # Public headers
│   ├── parser.hpp             # Main parser
│   ├── replay.hpp             # Replay model
│   ├── chunk.hpp              # Base chunk class
│   ├── chunk_type.hpp         # Chunk type enum
│   ├── header_chunk.hpp       # Header chunk
│   ├── data_chunk.hpp         # Data chunk
│   ├── checkpoint_chunk.hpp   # Checkpoint chunk
│   └── event_chunk.hpp        # Event chunk
├── src/                       # Implementation
│   ├── parser.cpp
│   └── replay.cpp
├── tests/                     # Unit tests
│   ├── test_parser.cpp
│   └── test_replay.cpp
├── examples/                  # Example programs
│   ├── example_main.cpp       # Replay viewer
│   └── README.md
├── generated/                 # Kaitai-generated code
│   └── fortnite_replay.cpp
└── .github/workflows/         # CI/CD
    └── ci.yml                 # GitHub Actions workflow
```

## Building from Source

### Using the build script (Recommended)

```bash
./build.sh
```

This script will:
1. Configure the project with CMake
2. Build all targets
3. Run all tests
4. Generate build artifacts in `build/`

### Manual CMake build

```bash
# Configure
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release --parallel

# Run tests
cd build
ctest -C Release --output-on-failure

# Install (optional)
sudo cmake --install build
```

### CMake Options

- `CMAKE_BUILD_TYPE`: Build type (Debug, Release, RelWithDebInfo, MinSizeRel)
- `CMAKE_INSTALL_PREFIX`: Installation directory
- `CMAKE_CXX_COMPILER`: C++ compiler to use

## Testing

The project includes comprehensive unit tests using Google Test.

```bash
# Run all tests
cd build
ctest --output-on-failure

# Run specific test
./fortnite_replay_tests --gtest_filter=ReplayTest.*

# Run tests with verbose output
ctest -V

# Skip Oodle-dependent tests (if oo2core library is not available)
SKIP_OODLE_TESTS=true ctest --output-on-failure
```

Test coverage includes:
- Parser functionality
- Replay model classes
- Chunk types and accessors
- Data structures (EngineVersion, ReplayInfo, etc.)
- Cryptography (AES decryption, Oodle decompression)
- Edge cases and error handling

**Note:** Tests requiring the oo2core library are automatically skipped when running in CI environments (when `CI=true` or `SKIP_OODLE_TESTS=true`). These tests will run locally if you have the oo2core library installed on your system.

## CI/CD

The project uses GitHub Actions for continuous integration:

- **Build and Test**: Builds on Linux, macOS, and Windows with both Debug and Release configurations
- **Code Coverage**: Generates coverage reports and uploads to Codecov
- **Static Analysis**: Runs cppcheck for static code analysis
- **Formatting Check**: Verifies code formatting with clang-format

Workflows run on:
- Every push to `main` branch
- Every pull request to `main` branch

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

### Development Setup

1. Fork the repository
2. Clone your fork: `git clone https://github.com/YOUR_USERNAME/fortnite-replay.git`
3. Create a branch: `git checkout -b feature/my-feature`
4. Make your changes and add tests
5. Run tests: `./build.sh`
6. Commit your changes: `git commit -am 'Add new feature'`
7. Push to the branch: `git push origin feature/my-feature`
8. Open a Pull Request

### Code Style

- Use C++23 features where appropriate
- Follow the existing code style
- Add tests for new functionality
- Document public APIs with comments
- Keep lines under 100 characters where reasonable

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built with [Kaitai Struct](https://kaitai.io/) for binary parsing
- Uses [Google Test](https://github.com/google/googletest) for testing
- Inspired by the Fortnite replay file format

## Related Projects

- [fortnite-replay-parser](https://github.com/xNocken/fortnite-replay-parser) - JavaScript implementation
- [FortniteReplayReader](https://github.com/Shiqan/FortniteReplayDecompressor) - C# implementation

## Support

- For bugs and feature requests, please [open an issue](https://github.com/linustg/fortnite-replay/issues)
- For questions and discussions, use [GitHub Discussions](https://github.com/linustg/fortnite-replay/discussions)

---

**Note**: This is an unofficial library and is not affiliated with Epic Games or Fortnite.
