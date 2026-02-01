#include "fortnite_replay/stores/event_store.hpp"
#include "fortnite_replay/replay.hpp"
#include <algorithm>

namespace fortnite_replay {

EventStore::EventStore(const Replay *replay) : m_replay(replay) {}

std::vector<const Event *> EventStore::all() const {
  auto events = m_replay->chunks_of_type<Event>();
  std::vector<const Event *> result;
  result.reserve(events.size());
  for (auto *event : events) {
    result.push_back(event);
  }
  return result;
}

std::vector<const Event *> EventStore::byType(EventType type) const {
  auto events = all();
  std::vector<const Event *> result;
  std::copy_if(events.begin(), events.end(), std::back_inserter(result),
               [type](const Event *e) { return e->event_type == type; });
  return result;
}

std::vector<const Event *> EventStore::eliminations() const {
  return byType(EventType::PlayerElimination);
}

std::vector<const Event *> EventStore::matchStats() const {
  return byType(EventType::MatchStats);
}

std::vector<const Event *> EventStore::teamStats() const {
  return byType(EventType::TeamStats);
}

std::vector<const Event *> EventStore::encryptionKeys() const {
  return byType(EventType::EncryptionKey);
}

std::vector<const Event *> EventStore::characterSamples() const {
  return byType(EventType::CharacterSample);
}

std::vector<const Event *> EventStore::zoneUpdates() const {
  return byType(EventType::ZoneUpdate);
}

std::vector<const Event *> EventStore::battleBus() const {
  return byType(EventType::BattleBus);
}

std::vector<const Event *> EventStore::inTimeRange(uint32_t start_ms,
                                                    uint32_t end_ms) const {
  auto events = all();
  std::vector<const Event *> result;
  std::copy_if(events.begin(), events.end(), std::back_inserter(result),
               [start_ms, end_ms](const Event *e) {
                 return e->start_time_ms <= end_ms && e->end_time_ms >= start_ms;
               });
  return result;
}

std::optional<const Event *> EventStore::atTime(uint32_t time_ms) const {
  auto events = all();
  auto it = std::find_if(events.begin(), events.end(), [time_ms](const Event *e) {
    return time_ms >= e->start_time_ms && time_ms <= e->end_time_ms;
  });
  if (it != events.end()) {
    return *it;
  }
  return std::nullopt;
}

size_t EventStore::count() const { return m_replay->chunks_of_type<Event>().size(); }

size_t EventStore::countByType(EventType type) const {
  return byType(type).size();
}

EventStore::const_iterator EventStore::begin() const {
  if (m_cached_events.empty()) {
    m_cached_events = all();
  }
  return m_cached_events.begin();
}

EventStore::const_iterator EventStore::end() const {
  if (m_cached_events.empty()) {
    m_cached_events = all();
  }
  return m_cached_events.end();
}

} // namespace fortnite_replay
