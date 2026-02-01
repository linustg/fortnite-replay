#ifndef FORTNITE_REPLAY_EVENT_PARSER_HPP
#define FORTNITE_REPLAY_EVENT_PARSER_HPP

#include "fortnite_replay.h"
#include <cstdint>
#include <span>

namespace fortnite_replay {

class Event;

/**
 * Parse an event chunk from the replay file
 *
 * @param event_chunk Raw event chunk data from the Kaitai-parsed replay
 * @param encryption_key Encryption key for decrypting event data (if encrypted)
 * @param is_encrypted Whether the event data is encrypted
 * @return Parsed Event object
 * @throws std::runtime_error if parsing fails
 */
Event parse_event_chunk(const fortnite_replay_t::event_chunk_t *event_chunk,
                        std::span<const uint8_t> encryption_key,
                        bool is_encrypted);

} // namespace fortnite_replay

#endif // FORTNITE_REPLAY_EVENT_PARSER_HPP
