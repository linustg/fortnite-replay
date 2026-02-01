#ifndef FORTNITE_REPLAY_STORES_EVENT_STORE_HPP
#define FORTNITE_REPLAY_STORES_EVENT_STORE_HPP

#include "fortnite_replay/event.hpp"
#include <cstdint>
#include <optional>
#include <vector>

namespace fortnite_replay {

class Replay;

/**
 * Store providing organized access to event chunks with filtering and querying
 */
class EventStore {
public:
  /**
   * Get all events
   */
  std::vector<const Event *> all() const;

  /**
   * Get events of a specific type
   */
  std::vector<const Event *> byType(EventType type) const;

  /**
   * Get all player elimination events
   */
  std::vector<const Event *> eliminations() const;

  /**
   * Get all match stats events
   */
  std::vector<const Event *> matchStats() const;

  /**
   * Get all team stats events
   */
  std::vector<const Event *> teamStats() const;

  /**
   * Get all encryption key events
   */
  std::vector<const Event *> encryptionKeys() const;

  /**
   * Get all character sample events
   */
  std::vector<const Event *> characterSamples() const;

  /**
   * Get all zone update events
   */
  std::vector<const Event *> zoneUpdates() const;

  /**
   * Get all battle bus events
   */
  std::vector<const Event *> battleBus() const;

  /**
   * Get events within a time range (inclusive)
   */
  std::vector<const Event *> inTimeRange(uint32_t start_ms,
                                          uint32_t end_ms) const;

  /**
   * Get event at a specific time (matches if time is within event's
   * start_time_ms and end_time_ms)
   */
  std::optional<const Event *> atTime(uint32_t time_ms) const;

  /**
   * Get total count of events
   */
  size_t count() const;

  /**
   * Get count of events by type
   */
  size_t countByType(EventType type) const;

  /**
   * Iterator support for range-based for loops
   */
  using const_iterator = std::vector<const Event *>::const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

private:
  friend class Replay;
  explicit EventStore(const Replay *replay);

  const Replay *m_replay;
  mutable std::vector<const Event *>
      m_cached_events; // Cached for iterator support
};

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_STORES_EVENT_STORE_HPP
