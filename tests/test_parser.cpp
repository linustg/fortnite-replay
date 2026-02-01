#include "fortnite_replay/parser.hpp"
#include <gtest/gtest.h>

class FortniteReplayParserTest : public ::testing::Test {
protected:
  static constexpr const char *TEST_REPLAY_PATH =
      "tests/data/replays/chapter5season5.replay";
};

TEST_F(FortniteReplayParserTest, ParseValidReplay) {
  fortnite_replay::FortniteReplayParser parser;
  ASSERT_TRUE(parser.parse(TEST_REPLAY_PATH));
  EXPECT_TRUE(parser.is_valid());
}

TEST_F(FortniteReplayParserTest, ParseNonExistentFile) {
  fortnite_replay::FortniteReplayParser parser;
  EXPECT_FALSE(parser.parse("nonexistent.replay"));
  EXPECT_FALSE(parser.is_valid());
}

TEST_F(FortniteReplayParserTest, FileVersion) {
  fortnite_replay::FortniteReplayParser parser;
  ASSERT_TRUE(parser.parse(TEST_REPLAY_PATH));
  EXPECT_GT(parser.file_version(), 0u);
}

TEST_F(FortniteReplayParserTest, ReplayMetadata) {
  fortnite_replay::FortniteReplayParser parser;
  ASSERT_TRUE(parser.parse(TEST_REPLAY_PATH));

  EXPECT_GT(parser.length_in_ms(), 0u);
  EXPECT_GT(parser.network_version(), 0u);
  EXPECT_GT(parser.changelist(), 0u);
}

TEST_F(FortniteReplayParserTest, FriendlyName) {
  fortnite_replay::FortniteReplayParser parser;
  ASSERT_TRUE(parser.parse(TEST_REPLAY_PATH));

  std::string name = parser.friendly_name();
  EXPECT_FALSE(name.empty());
}

TEST_F(FortniteReplayParserTest, Timestamp) {
  fortnite_replay::FortniteReplayParser parser;
  ASSERT_TRUE(parser.parse(TEST_REPLAY_PATH));
  EXPECT_GT(parser.timestamp(), 0u);
}

TEST_F(FortniteReplayParserTest, MoveSemantics) {
  fortnite_replay::FortniteReplayParser parser1;
  ASSERT_TRUE(parser1.parse(TEST_REPLAY_PATH));

  fortnite_replay::FortniteReplayParser parser2 = std::move(parser1);
  EXPECT_TRUE(parser2.is_valid());
}
