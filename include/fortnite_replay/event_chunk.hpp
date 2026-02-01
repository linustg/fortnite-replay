#ifndef FORTNITE_REPLAY_EVENT_CHUNK_HPP
#define FORTNITE_REPLAY_EVENT_CHUNK_HPP

#include "chunk.hpp"
#include "chunk_type.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace fortnite_replay {
namespace event_type {
inline constexpr const char *PLAYER_ELIMINATION = "playerElim";
inline constexpr const char *MATCH_STATS = "AthenaMatchStats";
inline constexpr const char *TEAM_STATS = "AthenaMatchTeamStats";
inline constexpr const char *ENCRYPTION_KEY = "PlayerStateEncryptionKey";
inline constexpr const char *CHARACTER_SAMPLE = "CharacterSampleMeta";
inline constexpr const char *ZONE_UPDATE = "ZoneUpdate";
inline constexpr const char *BATTLE_BUS = "BattleBusFlight";
} // namespace event_type

enum class EventType {
  PlayerElimination,
  MatchStats,
  TeamStats,
  EncryptionKey,
  CharacterSample,
  ZoneUpdate,
  BattleBus,
  Unknown
};

/**
 * Event chunk for game-specific events (kills, stats, etc.)
 */
class EventChunk : public Chunk {
public:
  EventChunk() = default;

  ChunkType type() const override { return ChunkType::Event; }
  const char *type_name() const override { return "Event"; }

  std::string id;
  EventType event_type = EventType::Unknown;
  std::string metadata;
  uint32_t start_time_ms = 0;
  uint32_t end_time_ms = 0;
  std::vector<uint8_t> data; // Raw event data

  /**
   * Get duration of this event in milliseconds
   */
  uint32_t duration_ms() const {
    return end_time_ms > start_time_ms ? end_time_ms - start_time_ms : 0;
  }
};

// Type alias for backward compatibility
using Event = EventChunk;

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_EVENT_CHUNK_HPP
