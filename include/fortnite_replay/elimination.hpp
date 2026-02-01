#ifndef FORTNITE_REPLAY_ELIMINATION_HPP
#define FORTNITE_REPLAY_ELIMINATION_HPP

#include "event.hpp"
#include <cstdint>
#include <string>

namespace fortnite_replay {

class Elimination : public Event {
public:
  Elimination() = default;
  ~Elimination() = default;

  std::string eliminated_player_id;
  std::string eliminator_player_id;
  uint8_t weapon_type;
  bool knocked_down;
};

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_ELIMINATION_HPP