#ifndef FORTNITE_REPLAY_UTILS_HPP
#define FORTNITE_REPLAY_UTILS_HPP

#include "fortnite_replay/event_chunk.hpp"

namespace fortnite_replay::Utils {

/** Helper to convert string event ID to EventType enum */
inline EventType string_to_event_type(const std::string &type_str) {
  if (type_str == event_type::PLAYER_ELIMINATION)
    return EventType::PlayerElimination;
  if (type_str == event_type::MATCH_STATS)
    return EventType::MatchStats;
  if (type_str == event_type::TEAM_STATS)
    return EventType::TeamStats;
  if (type_str == event_type::ENCRYPTION_KEY)
    return EventType::EncryptionKey;
  if (type_str == event_type::CHARACTER_SAMPLE)
    return EventType::CharacterSample;
  if (type_str == event_type::ZONE_UPDATE)
    return EventType::ZoneUpdate;
  if (type_str == event_type::BATTLE_BUS)
    return EventType::BattleBus;
  return EventType::Unknown;
}

/** Helper to convert EventType enum to string */
inline std::string event_type_to_string(EventType type) {
  switch (type) {
  case EventType::PlayerElimination:
    return event_type::PLAYER_ELIMINATION;
  case EventType::MatchStats:
    return event_type::MATCH_STATS;
  case EventType::TeamStats:
    return event_type::TEAM_STATS;
  case EventType::EncryptionKey:
    return event_type::ENCRYPTION_KEY;
  case EventType::CharacterSample:
    return event_type::CHARACTER_SAMPLE;
  case EventType::ZoneUpdate:
    return event_type::ZONE_UPDATE;
  case EventType::BattleBus:
    return event_type::BATTLE_BUS;
  default:
    return "Unknown";
  }
}

} // namespace fortnite_replay::Utils

#endif // FORTNITE_REPLAY_UTILS_HPP