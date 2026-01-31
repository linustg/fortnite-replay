#include <gtest/gtest.h>
#include "fortnite_replay/replay.hpp"
#include "fortnite_replay/parser.hpp"

using namespace fortnite_replay;

class ReplayModelTest : public ::testing::Test
{
protected:
    static constexpr const char *TEST_REPLAY_PATH =
        "tests/data/replays/chapter5season5.replay";
};

// ============================================================================
// ChunkType Tests
// ============================================================================

TEST(ChunkTypeTest, EnumValues)
{
    EXPECT_EQ(static_cast<uint32_t>(ChunkType::Header), 0u);
    EXPECT_EQ(static_cast<uint32_t>(ChunkType::ReplayData), 1u);
    EXPECT_EQ(static_cast<uint32_t>(ChunkType::Checkpoint), 2u);
    EXPECT_EQ(static_cast<uint32_t>(ChunkType::Event), 3u);
    EXPECT_EQ(static_cast<uint32_t>(ChunkType::Unknown), 0xFFFFFFFFu);
}

// ============================================================================
// Chunk Base Class Tests
// ============================================================================

TEST(ChunkTest, HeaderChunkType)
{
    HeaderChunk chunk;
    EXPECT_EQ(chunk.type(), ChunkType::Header);
    EXPECT_STREQ(chunk.type_name(), "Header");
}

TEST(ChunkTest, DataChunkType)
{
    DataChunk chunk;
    EXPECT_EQ(chunk.type(), ChunkType::ReplayData);
    EXPECT_STREQ(chunk.type_name(), "ReplayData");
}

TEST(ChunkTest, CheckpointChunkType)
{
    CheckpointChunk chunk;
    EXPECT_EQ(chunk.type(), ChunkType::Checkpoint);
    EXPECT_STREQ(chunk.type_name(), "Checkpoint");
}

TEST(ChunkTest, EventChunkType)
{
    EventChunk chunk;
    EXPECT_EQ(chunk.type(), ChunkType::Event);
    EXPECT_STREQ(chunk.type_name(), "Event");
}

TEST(ChunkTest, PolymorphicAccess)
{
    std::vector<std::unique_ptr<Chunk>> chunks;
    chunks.push_back(std::make_unique<HeaderChunk>());
    chunks.push_back(std::make_unique<DataChunk>());
    chunks.push_back(std::make_unique<CheckpointChunk>());
    chunks.push_back(std::make_unique<EventChunk>());

    EXPECT_EQ(chunks[0]->type(), ChunkType::Header);
    EXPECT_EQ(chunks[1]->type(), ChunkType::ReplayData);
    EXPECT_EQ(chunks[2]->type(), ChunkType::Checkpoint);
    EXPECT_EQ(chunks[3]->type(), ChunkType::Event);
}

// ============================================================================
// EngineVersion Tests
// ============================================================================

TEST(EngineVersionTest, DefaultConstruction)
{
    EngineVersion version;
    EXPECT_EQ(version.major, 0);
    EXPECT_EQ(version.minor, 0);
    EXPECT_EQ(version.patch, 0);
    EXPECT_EQ(version.changelist, 0);
    EXPECT_TRUE(version.branch.empty());
}

TEST(EngineVersionTest, ToString)
{
    EngineVersion version{5, 4, 1, 12345678, "++Fortnite+Release"};
    EXPECT_EQ(version.to_string(), "5.4.1");
}

TEST(EngineVersionTest, ToStringZeroVersion)
{
    EngineVersion version;
    EXPECT_EQ(version.to_string(), "0.0.0");
}

// ============================================================================
// ReplayHeaderFlags Tests
// ============================================================================

TEST(ReplayHeaderFlagsTest, FromBitmaskNone)
{
    auto flags = ReplayHeaderFlags::from_bitmask(0);
    EXPECT_FALSE(flags.client_recorded);
    EXPECT_FALSE(flags.has_streaming_fixes);
    EXPECT_FALSE(flags.delta_checkpoints);
    EXPECT_FALSE(flags.game_specific_frame_data);
    EXPECT_FALSE(flags.replay_connection);
    EXPECT_FALSE(flags.actor_prioritization_enabled);
    EXPECT_FALSE(flags.net_relevancy_enabled);
    EXPECT_FALSE(flags.async_recorded);
}

TEST(ReplayHeaderFlagsTest, FromBitmaskClientRecorded)
{
    auto flags = ReplayHeaderFlags::from_bitmask(1);
    EXPECT_TRUE(flags.client_recorded);
    EXPECT_FALSE(flags.has_streaming_fixes);
}

TEST(ReplayHeaderFlagsTest, FromBitmaskMultipleFlags)
{
    // client_recorded (1) + delta_checkpoints (4) + async_recorded (128) = 133
    auto flags = ReplayHeaderFlags::from_bitmask(133);
    EXPECT_TRUE(flags.client_recorded);
    EXPECT_FALSE(flags.has_streaming_fixes);
    EXPECT_TRUE(flags.delta_checkpoints);
    EXPECT_FALSE(flags.game_specific_frame_data);
    EXPECT_FALSE(flags.replay_connection);
    EXPECT_FALSE(flags.actor_prioritization_enabled);
    EXPECT_FALSE(flags.net_relevancy_enabled);
    EXPECT_TRUE(flags.async_recorded);
}

TEST(ReplayHeaderFlagsTest, FromBitmaskAllFlags)
{
    auto flags = ReplayHeaderFlags::from_bitmask(0xFF);
    EXPECT_TRUE(flags.client_recorded);
    EXPECT_TRUE(flags.has_streaming_fixes);
    EXPECT_TRUE(flags.delta_checkpoints);
    EXPECT_TRUE(flags.game_specific_frame_data);
    EXPECT_TRUE(flags.replay_connection);
    EXPECT_TRUE(flags.actor_prioritization_enabled);
    EXPECT_TRUE(flags.net_relevancy_enabled);
    EXPECT_TRUE(flags.async_recorded);
}

// ============================================================================
// ReplayInfo Tests
// ============================================================================

TEST(ReplayInfoTest, DefaultConstruction)
{
    ReplayInfo info;
    EXPECT_EQ(info.file_version, 0);
    EXPECT_EQ(info.length_ms, 0);
    EXPECT_EQ(info.network_version, 0);
    EXPECT_EQ(info.changelist, 0);
    EXPECT_TRUE(info.friendly_name.empty());
    EXPECT_FALSE(info.is_live);
    EXPECT_FALSE(info.timestamp.has_value());
    EXPECT_FALSE(info.is_compressed);
    EXPECT_FALSE(info.is_encrypted);
    EXPECT_TRUE(info.encryption_key.empty());
}

TEST(ReplayInfoTest, Duration)
{
    ReplayInfo info;
    info.length_ms = 60000; // 1 minute
    EXPECT_EQ(info.duration().count(), 60000);
}

TEST(ReplayInfoTest, DurationZero)
{
    ReplayInfo info;
    EXPECT_EQ(info.duration().count(), 0);
}

// ============================================================================
// Replay Class Tests
// ============================================================================

TEST(ReplayTest, DefaultConstruction)
{
    Replay replay;
    EXPECT_TRUE(replay.friendly_name().empty());
    EXPECT_EQ(replay.duration().count(), 0);
    EXPECT_FALSE(replay.is_compressed());
    EXPECT_FALSE(replay.is_encrypted());
    EXPECT_FALSE(replay.is_live());
    EXPECT_EQ(replay.chunk_count(), 0);
    EXPECT_EQ(replay.frame_count(), 0);
    EXPECT_EQ(replay.checkpoint_count(), 0);
    EXPECT_EQ(replay.event_count(), 0);
}

TEST(ReplayTest, InfoAccessors)
{
    Replay replay;
    replay.info().friendly_name = "Test Replay";
    replay.info().length_ms = 120000;
    replay.info().is_compressed = true;

    EXPECT_EQ(replay.friendly_name(), "Test Replay");
    EXPECT_EQ(replay.duration().count(), 120000);
    EXPECT_TRUE(replay.is_compressed());
}

TEST(ReplayTest, AddHeaderChunk)
{
    Replay replay;
    EXPECT_EQ(replay.header_chunk(), nullptr);

    auto &header = replay.add_chunk<HeaderChunk>();
    header.network_version = 19;
    header.network_checksum = 12345;

    EXPECT_NE(replay.header_chunk(), nullptr);
    EXPECT_EQ(replay.header_chunk()->network_version, 19);
    EXPECT_EQ(replay.header_chunk()->network_checksum, 12345);
    EXPECT_EQ(replay.chunk_count(), 1);
}

TEST(ReplayTest, AddDataChunks)
{
    Replay replay;
    EXPECT_EQ(replay.frame_count(), 0);

    auto &frame1 = replay.add_chunk<DataChunk>();
    frame1.start_time_ms = 0;
    frame1.end_time_ms = 1000;
    frame1.data_length = 100;
    frame1.memory_size_bytes = 200;

    auto &frame2 = replay.add_chunk<DataChunk>();
    frame2.start_time_ms = 1000;
    frame2.end_time_ms = 2000;
    frame2.data_length = 150;
    frame2.memory_size_bytes = 300;

    EXPECT_EQ(replay.frame_count(), 2);
    EXPECT_EQ(replay.chunk_count(), 2);

    auto data_chunks = replay.data_chunks();
    EXPECT_EQ(data_chunks.size(), 2);
    EXPECT_EQ(data_chunks[0]->start_time_ms, 0);
    EXPECT_EQ(data_chunks[0]->end_time_ms, 1000);
    EXPECT_EQ(data_chunks[1]->start_time_ms, 1000);
}

TEST(ReplayTest, AddCheckpointChunks)
{
    Replay replay;
    EXPECT_EQ(replay.checkpoint_count(), 0);

    auto &cp = replay.add_chunk<CheckpointChunk>();
    cp.id = "checkpoint_1";
    cp.group = "PlayerState";
    cp.start_time_ms = 5000;
    cp.end_time_ms = 5000;

    EXPECT_EQ(replay.checkpoint_count(), 1);

    auto checkpoints = replay.checkpoint_chunks();
    EXPECT_EQ(checkpoints.size(), 1);
    EXPECT_EQ(checkpoints[0]->id, "checkpoint_1");
    EXPECT_EQ(checkpoints[0]->group, "PlayerState");
}

TEST(ReplayTest, AddEventChunks)
{
    Replay replay;
    EXPECT_EQ(replay.event_count(), 0);

    auto &event = replay.add_chunk<EventChunk>();
    event.id = "kill_1";
    event.group = "playerElim";
    event.metadata = "HeadShot";
    event.start_time_ms = 30000;
    event.end_time_ms = 30000;

    EXPECT_EQ(replay.event_count(), 1);

    auto events = replay.event_chunks();
    EXPECT_EQ(events.size(), 1);
    EXPECT_EQ(events[0]->id, "kill_1");
    EXPECT_EQ(events[0]->group, "playerElim");
    EXPECT_EQ(events[0]->metadata, "HeadShot");
}

TEST(ReplayTest, MixedChunkTypes)
{
    Replay replay;

    replay.add_chunk<HeaderChunk>();
    replay.add_chunk<DataChunk>();
    replay.add_chunk<DataChunk>();
    replay.add_chunk<CheckpointChunk>();
    replay.add_chunk<EventChunk>();
    replay.add_chunk<DataChunk>();
    replay.add_chunk<EventChunk>();

    EXPECT_EQ(replay.chunk_count(), 7);
    EXPECT_EQ(replay.frame_count(), 3);
    EXPECT_EQ(replay.checkpoint_count(), 1);
    EXPECT_EQ(replay.event_count(), 2);
    EXPECT_NE(replay.header_chunk(), nullptr);
}

TEST(ReplayTest, ChunksOfType)
{
    Replay replay;

    replay.add_chunk<HeaderChunk>();
    replay.add_chunk<DataChunk>();
    replay.add_chunk<EventChunk>();
    replay.add_chunk<DataChunk>();

    auto headers = replay.chunks_of_type<HeaderChunk>();
    auto data = replay.chunks_of_type<DataChunk>();
    auto events = replay.chunks_of_type<EventChunk>();
    auto checkpoints = replay.chunks_of_type<CheckpointChunk>();

    EXPECT_EQ(headers.size(), 1);
    EXPECT_EQ(data.size(), 2);
    EXPECT_EQ(events.size(), 1);
    EXPECT_EQ(checkpoints.size(), 0);
}

TEST(ReplayTest, BackwardCompatibleHeader)
{
    Replay replay;
    EXPECT_FALSE(replay.header().has_value());

    auto &header = replay.add_chunk<HeaderChunk>();
    header.network_version = 19;

    // Backward-compatible accessor returns a copy
    auto optional_header = replay.header();
    EXPECT_TRUE(optional_header.has_value());
    EXPECT_EQ(optional_header->network_version, 19);
}

TEST(ReplayTest, BackwardCompatibleDataFrames)
{
    Replay replay;

    auto &frame = replay.add_chunk<DataChunk>();
    frame.start_time_ms = 100;

    // Backward-compatible accessor returns copies
    auto frames = replay.data_frames();
    EXPECT_EQ(frames.size(), 1);
    EXPECT_EQ(frames[0].start_time_ms, 100);
}

TEST(ReplayTest, ConstAccessors)
{
    Replay replay;
    replay.info().friendly_name = "Const Test";
    replay.add_chunk<DataChunk>();
    replay.add_chunk<CheckpointChunk>();
    replay.add_chunk<EventChunk>();

    const Replay &const_replay = replay;
    EXPECT_EQ(const_replay.info().friendly_name, "Const Test");
    EXPECT_EQ(const_replay.chunks().size(), 3);
    EXPECT_EQ(const_replay.data_chunks().size(), 1);
    EXPECT_EQ(const_replay.checkpoint_chunks().size(), 1);
    EXPECT_EQ(const_replay.event_chunks().size(), 1);
}

// ============================================================================
// DataChunk Tests
// ============================================================================

TEST(DataChunkTest, DefaultConstruction)
{
    DataChunk frame;
    EXPECT_EQ(frame.start_time_ms, 0);
    EXPECT_EQ(frame.end_time_ms, 0);
    EXPECT_EQ(frame.data_length, 0);
    EXPECT_EQ(frame.memory_size_bytes, 0);
    EXPECT_TRUE(frame.data.empty());
}

TEST(DataChunkTest, DurationMs)
{
    DataChunk frame;
    frame.start_time_ms = 1000;
    frame.end_time_ms = 2500;
    EXPECT_EQ(frame.duration_ms(), 1500);
}

TEST(DataChunkTest, DurationMsZero)
{
    DataChunk frame;
    frame.start_time_ms = 1000;
    frame.end_time_ms = 1000;
    EXPECT_EQ(frame.duration_ms(), 0);
}

// ============================================================================
// CheckpointChunk Tests
// ============================================================================

TEST(CheckpointChunkTest, DefaultConstruction)
{
    CheckpointChunk cp;
    EXPECT_TRUE(cp.id.empty());
    EXPECT_TRUE(cp.group.empty());
    EXPECT_TRUE(cp.metadata.empty());
    EXPECT_EQ(cp.start_time_ms, 0);
    EXPECT_EQ(cp.end_time_ms, 0);
    EXPECT_TRUE(cp.data.empty());
}

TEST(CheckpointChunkTest, DurationMs)
{
    CheckpointChunk cp;
    cp.start_time_ms = 5000;
    cp.end_time_ms = 5500;
    EXPECT_EQ(cp.duration_ms(), 500);
}

// ============================================================================
// EventChunk Tests
// ============================================================================

TEST(EventChunkTest, DefaultConstruction)
{
    EventChunk event;
    EXPECT_TRUE(event.id.empty());
    EXPECT_TRUE(event.group.empty());
    EXPECT_TRUE(event.metadata.empty());
    EXPECT_EQ(event.start_time_ms, 0);
    EXPECT_EQ(event.end_time_ms, 0);
    EXPECT_TRUE(event.data.empty());
}

TEST(EventChunkTest, DurationMs)
{
    EventChunk event;
    event.start_time_ms = 10000;
    event.end_time_ms = 10100;
    EXPECT_EQ(event.duration_ms(), 100);
}

// ============================================================================
// Supporting Structure Tests
// ============================================================================

TEST(LevelInfoTest, Construction)
{
    LevelInfo level{"Athena_Terrain", 0};
    EXPECT_EQ(level.name, "Athena_Terrain");
    EXPECT_EQ(level.time_ms, 0);
}

TEST(PackageVersionInfoTest, DefaultConstruction)
{
    PackageVersionInfo pkg;
    EXPECT_EQ(pkg.min_record_hz, 0.0f);
    EXPECT_EQ(pkg.max_record_hz, 0.0f);
    EXPECT_EQ(pkg.frame_limit_ms, 0.0f);
    EXPECT_EQ(pkg.checkpoint_limit_ms, 0.0f);
    EXPECT_TRUE(pkg.platform.empty());
    EXPECT_EQ(pkg.build_config, 0);
    EXPECT_EQ(pkg.build_target_type, 0);
}

TEST(RecordingMetadataTest, DefaultConstruction)
{
    RecordingMetadata meta;
    EXPECT_EQ(meta.ue4_version, 0);
    EXPECT_EQ(meta.ue5_version, 0);
    EXPECT_EQ(meta.package_version_licensee_ue, 0);
}

TEST(CustomVersionTest, Construction)
{
    CustomVersion cv{"some-guid-here", 42};
    EXPECT_EQ(cv.guid, "some-guid-here");
    EXPECT_EQ(cv.version, 42);
}

// ============================================================================
// HeaderChunk Tests
// ============================================================================

TEST(HeaderChunkTest, DefaultConstruction)
{
    HeaderChunk header;
    EXPECT_EQ(header.network_version, 0);
    EXPECT_EQ(header.network_checksum, 0);
    EXPECT_EQ(header.engine_network_version, 0);
    EXPECT_EQ(header.game_network_protocol_version, 0);
    EXPECT_TRUE(header.guid.empty());
    EXPECT_FALSE(header.engine_version.has_value());
    EXPECT_FALSE(header.recording_metadata.has_value());
    EXPECT_TRUE(header.levels.empty());
    EXPECT_TRUE(header.game_specific_data.empty());
    EXPECT_FALSE(header.package_version_info.has_value());
    EXPECT_TRUE(header.custom_versions.empty());
}

TEST(HeaderChunkTest, WithEngineVersion)
{
    HeaderChunk header;
    header.engine_version = EngineVersion{5, 4, 1, 12345678, "++Fortnite+Release"};

    EXPECT_TRUE(header.engine_version.has_value());
    EXPECT_EQ(header.engine_version->major, 5);
    EXPECT_EQ(header.engine_version->minor, 4);
    EXPECT_EQ(header.engine_version->to_string(), "5.4.1");
}

TEST(HeaderChunkTest, WithLevels)
{
    HeaderChunk header;
    header.levels.push_back(LevelInfo{"/Game/Athena/Maps/Athena_Terrain", 0});
    header.levels.push_back(LevelInfo{"/Game/Athena/Maps/Athena_POI_01", 100});

    EXPECT_EQ(header.levels.size(), 2);
    EXPECT_EQ(header.levels[0].name, "/Game/Athena/Maps/Athena_Terrain");
    EXPECT_EQ(header.levels[1].time_ms, 100);
}

// ============================================================================
// Integration Tests with Parser
// ============================================================================

TEST_F(ReplayModelTest, ParseAndGetReplay)
{
    FortniteReplayParser parser;
    if (!parser.parse(TEST_REPLAY_PATH))
    {
        GTEST_SKIP() << "Test replay file not available";
    }

    Replay replay = parser.replay();

    // Basic info should be populated
    EXPECT_FALSE(replay.friendly_name().empty());
    EXPECT_GT(replay.duration().count(), 0);
    EXPECT_GT(replay.info().file_version, 0u);
    EXPECT_GT(replay.info().network_version, 0u);
    EXPECT_GT(replay.info().changelist, 0u);
}

TEST_F(ReplayModelTest, ReplayHeader)
{
    FortniteReplayParser parser;
    if (!parser.parse(TEST_REPLAY_PATH))
    {
        GTEST_SKIP() << "Test replay file not available";
    }

    Replay replay = parser.replay();

    // Header should be present
    EXPECT_NE(replay.header_chunk(), nullptr);
    if (auto *header = replay.header_chunk())
    {
        EXPECT_GT(header->network_version, 0u);
        EXPECT_GT(header->engine_network_version, 0u);
    }
}

TEST_F(ReplayModelTest, ReplayContainsChunks)
{
    FortniteReplayParser parser;
    if (!parser.parse(TEST_REPLAY_PATH))
    {
        GTEST_SKIP() << "Test replay file not available";
    }

    Replay replay = parser.replay();

    // A valid replay should have chunks
    EXPECT_GT(replay.chunk_count(), 0);
    EXPECT_GT(replay.frame_count(), 0);
}

TEST_F(ReplayModelTest, ReplayEventsAndCheckpoints)
{
    FortniteReplayParser parser;
    if (!parser.parse(TEST_REPLAY_PATH))
    {
        GTEST_SKIP() << "Test replay file not available";
    }

    Replay replay = parser.replay();

    // Events and checkpoints may or may not be present depending on replay
    // Just verify we can access them without crashing
    for (auto *event : replay.event_chunks())
    {
        EXPECT_GE(event->start_time_ms, 0u);
    }

    for (auto *checkpoint : replay.checkpoint_chunks())
    {
        EXPECT_GE(checkpoint->start_time_ms, 0u);
    }
}

TEST_F(ReplayModelTest, EmptyParserReturnsEmptyReplay)
{
    FortniteReplayParser parser;
    // Don't parse anything

    Replay replay = parser.replay();

    EXPECT_TRUE(replay.friendly_name().empty());
    EXPECT_EQ(replay.duration().count(), 0);
    EXPECT_EQ(replay.chunk_count(), 0);
    EXPECT_EQ(replay.frame_count(), 0);
    EXPECT_EQ(replay.checkpoint_count(), 0);
    EXPECT_EQ(replay.event_count(), 0);
    EXPECT_EQ(replay.header_chunk(), nullptr);
}
