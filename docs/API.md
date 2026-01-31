# API Documentation

This document provides detailed API documentation for the Fortnite Replay Parser library.

## Table of Contents

- [Parser API](#parser-api)
- [Replay Model API](#replay-model-api)
- [Chunk Types](#chunk-types)
- [Data Structures](#data-structures)
- [Enumerations](#enumerations)

## Parser API

### `FortniteReplayParser`

The main class for parsing Fortnite replay files.

#### Constructor

```cpp
FortniteReplayParser();
```

Creates a new parser instance.

#### Methods

##### `parse()`

```cpp
bool parse(const std::string& filepath);
```

Parses a replay file from the specified path.

**Parameters:**
- `filepath`: Absolute or relative path to the .replay file

**Returns:**
- `true` if parsing succeeded
- `false` if parsing failed (file not found, invalid format, etc.)

**Example:**
```cpp
FortniteReplayParser parser;
if (parser.parse("my_replay.replay")) {
    // Success
}
```

##### `replay()`

```cpp
Replay replay();
```

Returns the parsed replay object containing all replay data.

**Returns:** `Replay` object with all parsed data

**Note:** Returns an empty replay if `parse()` was not called or failed.

##### `is_valid()`

```cpp
bool is_valid() const;
```

Checks if the parser contains valid replay data.

**Returns:** `true` if valid data is loaded, `false` otherwise

#### Legacy Accessors

These methods provide direct access to replay info fields:

```cpp
std::string magic() const;
uint32_t file_version() const;
uint32_t length_in_ms() const;
uint32_t network_version() const;
uint32_t changelist() const;
std::string friendly_name() const;
bool is_live() const;
uint64_t timestamp() const;
bool is_compressed() const;
```

**Note:** It's recommended to use the `Replay` object API instead.

---

## Replay Model API

### `Replay`

Main container for all replay data.

#### Info Accessors

##### `info()`

```cpp
const ReplayInfo& info() const;
ReplayInfo& info();
```

Access the replay metadata structure.

**Returns:** Reference to `ReplayInfo` structure

##### Convenience Accessors

```cpp
std::string friendly_name() const;
std::chrono::milliseconds duration() const;
bool is_compressed() const;
bool is_encrypted() const;
bool is_live() const;
```

These provide direct access to common replay properties.

#### Chunk Accessors

##### `header_chunk()`

```cpp
HeaderChunk* header_chunk() const;
```

Get the header chunk (network/version information).

**Returns:** Pointer to `HeaderChunk` or `nullptr` if not found

##### `data_chunks()`

```cpp
std::vector<DataChunk*> data_chunks() const;
```

Get all data chunks (network replay frames).

**Returns:** Vector of pointers to `DataChunk` objects

##### `checkpoint_chunks()`

```cpp
std::vector<CheckpointChunk*> checkpoint_chunks() const;
```

Get all checkpoint chunks.

**Returns:** Vector of pointers to `CheckpointChunk` objects

##### `event_chunks()`

```cpp
std::vector<EventChunk*> event_chunks() const;
```

Get all event chunks.

**Returns:** Vector of pointers to `EventChunk` objects

##### `chunks_of_type<T>()`

```cpp
template<typename T>
std::vector<T*> chunks_of_type() const;
```

Get all chunks of a specific type.

**Template Parameter:** Chunk type (e.g., `DataChunk`, `EventChunk`)

**Returns:** Vector of pointers to chunks of type `T`

**Example:**
```cpp
auto events = replay.chunks_of_type<EventChunk>();
```

#### Statistics

```cpp
size_t chunk_count() const;      // Total chunks
size_t frame_count() const;      // Data chunks
size_t checkpoint_count() const; // Checkpoint chunks
size_t event_count() const;      // Event chunks
```

#### Adding Chunks

```cpp
template<typename T, typename... Args>
T& add_chunk(Args&&... args);
```

Add a new chunk to the replay.

**Template Parameter:** Chunk type
**Parameters:** Constructor arguments for the chunk

**Returns:** Reference to the newly created chunk

**Example:**
```cpp
auto& event = replay.add_chunk<EventChunk>();
event.id = "kill_1";
event.group = "playerElim";
```

---

## Chunk Types

All chunks inherit from the base `Chunk` class.

### Base `Chunk` Class

```cpp
class Chunk {
public:
    virtual ChunkType type() const = 0;
    virtual const char* type_name() const = 0;
    virtual ~Chunk() = default;
};
```

### `HeaderChunk`

Contains network and version information.

#### Fields

```cpp
uint32_t network_version;
uint32_t network_checksum;
uint32_t engine_network_version;
uint32_t game_network_protocol_version;
std::string guid;  // 16-byte GUID

std::optional<EngineVersion> engine_version;
std::optional<RecordingMetadata> recording_metadata;
std::vector<CustomVersion> custom_versions;
std::vector<LevelInfo> levels;

ReplayHeaderFlags flags;
std::vector<std::string> game_specific_data;
std::optional<PackageVersionInfo> package_version_info;
```

#### Methods

```cpp
ChunkType type() const override;      // Returns ChunkType::Header
const char* type_name() const override; // Returns "Header"
```

### `DataChunk`

Represents a network replay frame.

#### Fields

```cpp
uint32_t start_time_ms;
uint32_t end_time_ms;
uint32_t data_length;
int32_t memory_size_bytes;
std::vector<uint8_t> data;  // Raw frame data
```

#### Methods

```cpp
uint32_t duration_ms() const;  // Returns end_time_ms - start_time_ms
ChunkType type() const override;      // Returns ChunkType::ReplayData
const char* type_name() const override; // Returns "ReplayData"
```

### `CheckpointChunk`

Checkpoint for fast-forwarding through replay.

#### Fields

```cpp
std::string id;
std::string group;
std::string metadata;
uint32_t start_time_ms;
uint32_t end_time_ms;
std::vector<uint8_t> data;  // Raw checkpoint data
```

#### Methods

```cpp
uint32_t duration_ms() const;
ChunkType type() const override;      // Returns ChunkType::Checkpoint
const char* type_name() const override; // Returns "Checkpoint"
```

### `EventChunk`

Game-specific event (kills, stats, etc.).

#### Fields

```cpp
std::string id;
std::string group;
std::string metadata;
uint32_t start_time_ms;
uint32_t end_time_ms;
std::vector<uint8_t> data;  // Raw event data
```

#### Common Event Groups

- `"playerElim"` - Player elimination/kill events
- `"AthenaReplayBrowserEvents"` - Match statistics
- `"PlayerStateEncryptionKey"` - Encryption keys

#### Methods

```cpp
uint32_t duration_ms() const;
ChunkType type() const override;      // Returns ChunkType::Event
const char* type_name() const override; // Returns "Event"
```

---

## Data Structures

### `ReplayInfo`

Replay metadata from the file header.

```cpp
struct ReplayInfo {
    uint32_t file_version;
    uint32_t length_ms;
    uint32_t network_version;
    uint32_t changelist;
    std::string friendly_name;
    bool is_live;
    std::optional<int64_t> timestamp;  // .NET DateTime binary format
    bool is_compressed;
    bool is_encrypted;
    std::vector<uint8_t> encryption_key;
    std::vector<CustomVersion> custom_versions;

    std::chrono::milliseconds duration() const;
};
```

### `EngineVersion`

Unreal Engine version information.

```cpp
struct EngineVersion {
    uint16_t major;
    uint16_t minor;
    uint16_t patch;
    uint32_t changelist;
    std::string branch;

    std::string to_string() const;  // Returns "major.minor.patch"
};
```

**Example:**
```cpp
EngineVersion version{5, 4, 1, 12345678, "++Fortnite+Release-32.00"};
std::cout << version.to_string();  // Prints "5.4.1"
```

### `ReplayHeaderFlags`

Replay recording flags.

```cpp
struct ReplayHeaderFlags {
    bool client_recorded;
    bool has_streaming_fixes;
    bool delta_checkpoints;
    bool game_specific_frame_data;
    bool replay_connection;
    bool actor_prioritization_enabled;
    bool net_relevancy_enabled;
    bool async_recorded;

    static ReplayHeaderFlags from_bitmask(uint32_t flags);
};
```

### `LevelInfo`

Level/map information with time offset.

```cpp
struct LevelInfo {
    std::string name;  // e.g., "/Game/Athena/Maps/Athena_Terrain"
    uint32_t time_ms;
};
```

### `PackageVersionInfo`

Package version and platform information.

```cpp
struct PackageVersionInfo {
    float min_record_hz;
    float max_record_hz;
    float frame_limit_ms;
    float checkpoint_limit_ms;
    std::string platform;  // e.g., "WindowsClient"
    uint8_t build_config;
    uint8_t build_target_type;  // 0=Unknown, 1=Game, 2=Server, 3=Client, etc.
};
```

### `RecordingMetadata`

Recording metadata with version information.

```cpp
struct RecordingMetadata {
    uint32_t ue4_version;
    uint32_t ue5_version;
    uint32_t package_version_licensee_ue;
};
```

### `CustomVersion`

Custom version entry (GUID + version).

```cpp
struct CustomVersion {
    std::string guid;  // 16 bytes
    int32_t version;
};
```

---

## Enumerations

### `ChunkType`

Enumeration of chunk types.

```cpp
enum class ChunkType : uint32_t {
    Header = 0,
    ReplayData = 1,
    Checkpoint = 2,
    Event = 3,
    Unknown = 0xFFFFFFFF
};
```

**String Conversion:**

Each chunk type has a corresponding string name via `type_name()`:

```cpp
HeaderChunk header;
std::cout << header.type_name();  // Prints "Header"
```

---

## Usage Examples

### Complete Parsing Example

```cpp
#include "fortnite_replay/parser.hpp"
#include "fortnite_replay/replay.hpp"

using namespace fortnite_replay;

void analyze_replay(const std::string& path) {
    FortniteReplayParser parser;

    if (!parser.parse(path)) {
        std::cerr << "Failed to parse replay\n";
        return;
    }

    Replay replay = parser.replay();

    // Print basic info
    std::cout << "Name: " << replay.friendly_name() << "\n";
    std::cout << "Duration: " << replay.duration().count() / 1000.0 << " seconds\n";

    // Access header
    if (auto* header = replay.header_chunk()) {
        if (header->engine_version.has_value()) {
            std::cout << "Engine: " << header->engine_version->to_string() << "\n";
        }
    }

    // Count player eliminations
    int elim_count = 0;
    for (auto* event : replay.event_chunks()) {
        if (event->group == "playerElim") {
            elim_count++;
        }
    }
    std::cout << "Player eliminations: " << elim_count << "\n";
}
```

### Working with Chunks

```cpp
// Filter events by type
std::vector<EventChunk*> get_eliminations(const Replay& replay) {
    std::vector<EventChunk*> eliminations;

    for (auto* event : replay.event_chunks()) {
        if (event->group == "playerElim") {
            eliminations.push_back(event);
        }
    }

    return eliminations;
}

// Calculate total data size
size_t calculate_data_size(const Replay& replay) {
    size_t total = 0;

    for (auto* frame : replay.data_chunks()) {
        total += frame->data_length;
    }

    return total;
}
```

---

## Error Handling

The library uses return values and optional types for error handling:

```cpp
// Check parse result
if (!parser.parse(path)) {
    // Handle error - file not found, invalid format, etc.
}

// Check for optional values
if (header->engine_version.has_value()) {
    // Use header->engine_version.value()
}

// Check for null pointers
if (auto* header = replay.header_chunk()) {
    // Use header
}
```

---

## Thread Safety

The library is **not thread-safe**. If you need to access replay data from multiple threads:

1. Use external synchronization (mutexes)
2. Create separate `Replay` objects per thread (after parsing)
3. Avoid concurrent modification of the same `Replay` object

---

## Memory Management

- The library uses RAII and smart pointers internally
- Chunks are owned by the `Replay` object
- Chunk pointers returned by accessors remain valid as long as the `Replay` object exists
- Moving a `Replay` object invalidates all previously obtained chunk pointers

---

## Performance Considerations

- Parsing is I/O bound - use SSDs for better performance
- Large replay files (>100MB) may take several seconds to parse
- Accessing chunks by type uses dynamic_cast internally (relatively fast)
- The `chunks_of_type<T>()` method iterates through all chunks

---

## Backward Compatibility

The library provides backward-compatible accessors:

```cpp
std::optional<HeaderChunk> header() const;           // Use header_chunk() instead
std::vector<DataChunk> data_frames() const;          // Use data_chunks() instead
std::vector<CheckpointChunk> checkpoints() const;    // Use checkpoint_chunks() instead
std::vector<EventChunk> events() const;              // Use event_chunks() instead
```

These return copies rather than pointers. Prefer the pointer-based API for better performance.
