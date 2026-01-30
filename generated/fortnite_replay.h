#ifndef FORTNITE_REPLAY_H_
#define FORTNITE_REPLAY_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

class fortnite_replay_t;

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <set>
#include <vector>

#if KAITAI_STRUCT_VERSION < 11000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.11 or later is required"
#endif

/**
 * Fortnite replay file format (.replay), used by Fortnite and other UE games.
 * 
 * Based on FortniteReplayDecompressor project and Unreal Engine source code.
 * 
 * References:
 *   - https://github.com/EpicGames/UnrealEngine/blob/70bc980c6361d9a7d23f6d23ffe322a2d6ef16fb/Engine/Source/Runtime/NetworkReplayStreaming/LocalFileNetworkReplayStreaming/Private/LocalFileNetworkReplayStreaming.cpp
 *   - https://github.com/EpicGames/UnrealEngine/blob/811c1ce579564fa92ecc22d9b70cbe9c8a8e4b9a/Engine/Source/Runtime/Engine/Classes/Engine/DemoNetDriver.h
 */

class fortnite_replay_t : public kaitai::kstruct {

public:
    class checkpoint_chunk_t;
    class custom_version_array_t;
    class custom_version_entry_t;
    class engine_version_full_t;
    class event_chunk_t;
    class fstring_t;
    class fstring_array_t;
    class header_chunk_t;
    class level_name_and_time_t;
    class level_names_and_times_array_t;
    class package_version_info_t;
    class recording_metadata_t;
    class replay_chunk_t;
    class replay_data_chunk_t;
    class replay_info_t;

    enum build_target_type_t {
        BUILD_TARGET_TYPE_UNKNOWN = 0,
        BUILD_TARGET_TYPE_GAME = 1,
        BUILD_TARGET_TYPE_SERVER = 2,
        BUILD_TARGET_TYPE_CLIENT = 3,
        BUILD_TARGET_TYPE_EDITOR = 4,
        BUILD_TARGET_TYPE_PROGRAM = 5
    };
    static bool _is_defined_build_target_type_t(build_target_type_t v);

private:
    static const std::set<build_target_type_t> _values_build_target_type_t;
    static std::set<build_target_type_t> _build_values_build_target_type_t();

public:

    enum engine_network_version_history_t {
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_INITIAL = 1,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_REPLAY_BACKWARDS_COMPAT = 2,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_MAX_ACTOR_CHANNELS_CUSTOMIZATION = 3,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_REPCMD_CHECKSUM_REMOVE_PRINTF = 4,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_NEW_ACTOR_OVERRIDE_LEVEL = 5,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_CHANNEL_NAMES = 6,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_CHANNEL_CLOSE_REASON = 7,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_ACKS_INCLUDED_IN_HEADER = 8,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_NETEXPORT_SERIALIZATION = 9,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_NETEXPORT_SERIALIZE_FIX = 10,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_FAST_ARRAY_DELTA_STRUCT = 11,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_FIX_ENUM_SERIALIZATION = 12,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_OPTIONALLY_QUANTIZE_SPAWN_INFO = 13,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_JITTER_IN_HEADER = 14,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_CLASSNETCACHE_FULLNAME = 15,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_REPLAY_DORMANCY = 16,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_ENUM_SERIALIZATION_COMPAT = 17,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_SUBOBJECT_OUTER_CHAIN = 18,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_HITRESULT_INSTANCEHANDLE = 19,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_INTERFACE_PROPERTY_SERIALIZATION = 20,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_MONTAGE_PLAY_INST_ID_SERIALIZATION = 21,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_SERIALIZE_DOUBLE_VECTORS_AS_DOUBLES = 22,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_PACKED_VECTOR_LWC_SUPPORT = 23,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_PAWN_REMOTEVIEWPITCH = 24,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_REPMOVE_SERVERFRAME_AND_HANDLE = 25,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_21_AND_VIEWPITCH_ONLY_DO_NOT_USE = 26,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_PLACEHOLDER = 27,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_RUNTIME_FEATURES_COMPATIBILITY = 28,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_SOFTOBJECTPTR_NETGUIDS = 29,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_SUBOBJECT_DESTROY_FLAG = 30,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_GAMESTATE_REPLICATED_TIME_AS_DOUBLE = 31,
        ENGINE_NETWORK_VERSION_HISTORY_HISTORY_CUSTOMVERSION = 32,
        ENGINE_NETWORK_VERSION_HISTORY_DYNAMIC_MONTAGE_SERIALIZATION = 33,
        ENGINE_NETWORK_VERSION_HISTORY_PREDICTION_KEY_BASE_NOT_REPLICATED = 34,
        ENGINE_NETWORK_VERSION_HISTORY_REP_MOVE_OPTIONAL_ACCELERATION = 35,
        ENGINE_NETWORK_VERSION_HISTORY_CUSTOM_EXPORTS = 36
    };
    static bool _is_defined_engine_network_version_history_t(engine_network_version_history_t v);

private:
    static const std::set<engine_network_version_history_t> _values_engine_network_version_history_t;
    static std::set<engine_network_version_history_t> _build_values_engine_network_version_history_t();

public:

    enum network_version_history_t {
        NETWORK_VERSION_HISTORY_HISTORY_REPLAY_INITIAL = 1,
        NETWORK_VERSION_HISTORY_HISTORY_SAVE_ABS_TIME_MS = 2,
        NETWORK_VERSION_HISTORY_HISTORY_INCREASE_BUFFER = 3,
        NETWORK_VERSION_HISTORY_HISTORY_SAVE_ENGINE_VERSION = 4,
        NETWORK_VERSION_HISTORY_HISTORY_EXTRA_VERSION = 5,
        NETWORK_VERSION_HISTORY_HISTORY_MULTIPLE_LEVELS = 6,
        NETWORK_VERSION_HISTORY_HISTORY_MULTIPLE_LEVELS_TIME_CHANGES = 7,
        NETWORK_VERSION_HISTORY_HISTORY_DELETED_STARTUP_ACTORS = 8,
        NETWORK_VERSION_HISTORY_HISTORY_HEADER_FLAGS = 9,
        NETWORK_VERSION_HISTORY_HISTORY_LEVEL_STREAMING_FIXES = 10,
        NETWORK_VERSION_HISTORY_HISTORY_SAVE_FULL_ENGINE_VERSION = 11,
        NETWORK_VERSION_HISTORY_HISTORY_HEADER_GUID = 12,
        NETWORK_VERSION_HISTORY_HISTORY_CHARACTER_MOVEMENT = 13,
        NETWORK_VERSION_HISTORY_HISTORY_CHARACTER_MOVEMENT_NOINTERP = 14,
        NETWORK_VERSION_HISTORY_HISTORY_GUID_NAMETABLE = 15,
        NETWORK_VERSION_HISTORY_HISTORY_GUIDCACHE_CHECKSUMS = 16,
        NETWORK_VERSION_HISTORY_HISTORY_SAVE_PACKAGE_VERSION_UE = 17,
        NETWORK_VERSION_HISTORY_HISTORY_RECORDING_METADATA = 18,
        NETWORK_VERSION_HISTORY_HISTORY_USE_CUSTOM_VERSION = 19
    };
    static bool _is_defined_network_version_history_t(network_version_history_t v);

private:
    static const std::set<network_version_history_t> _values_network_version_history_t;
    static std::set<network_version_history_t> _build_values_network_version_history_t();

public:

    enum replay_chunk_type_t {
        REPLAY_CHUNK_TYPE_HEADER = 0,
        REPLAY_CHUNK_TYPE_REPLAY_DATA = 1,
        REPLAY_CHUNK_TYPE_CHECKPOINT = 2,
        REPLAY_CHUNK_TYPE_EVENT = 3,
        REPLAY_CHUNK_TYPE_UNKNOWN = 4294967295UL
    };
    static bool _is_defined_replay_chunk_type_t(replay_chunk_type_t v);

private:
    static const std::set<replay_chunk_type_t> _values_replay_chunk_type_t;
    static std::set<replay_chunk_type_t> _build_values_replay_chunk_type_t();

public:

    enum replay_header_flags_t {
        REPLAY_HEADER_FLAGS_NONE = 0,
        REPLAY_HEADER_FLAGS_CLIENT_RECORDED = 1,
        REPLAY_HEADER_FLAGS_HAS_STREAMING_FIXES = 2,
        REPLAY_HEADER_FLAGS_DELTA_CHECKPOINTS = 4,
        REPLAY_HEADER_FLAGS_GAME_SPECIFIC_FRAME_DATA = 8,
        REPLAY_HEADER_FLAGS_REPLAY_CONNECTION = 16,
        REPLAY_HEADER_FLAGS_ACTOR_PRIORITIZATION_ENABLED = 32,
        REPLAY_HEADER_FLAGS_NET_RELEVANCY_ENABLED = 64,
        REPLAY_HEADER_FLAGS_ASYNC_RECORDED = 128
    };
    static bool _is_defined_replay_header_flags_t(replay_header_flags_t v);

private:
    static const std::set<replay_header_flags_t> _values_replay_header_flags_t;
    static std::set<replay_header_flags_t> _build_values_replay_header_flags_t();

public:

    enum replay_version_history_t {
        REPLAY_VERSION_HISTORY_HISTORY_INITIAL = 0,
        REPLAY_VERSION_HISTORY_HISTORY_FIXEDSIZE_FRIENDLY_NAME = 1,
        REPLAY_VERSION_HISTORY_HISTORY_COMPRESSION = 2,
        REPLAY_VERSION_HISTORY_HISTORY_RECORDED_TIMESTAMP = 3,
        REPLAY_VERSION_HISTORY_HISTORY_STREAM_CHUNK_TIMES = 4,
        REPLAY_VERSION_HISTORY_HISTORY_FRIENDLY_NAME_ENCODING = 5,
        REPLAY_VERSION_HISTORY_HISTORY_ENCRYPTION = 6,
        REPLAY_VERSION_HISTORY_HISTORY_CUSTOM_VERSIONS = 7
    };
    static bool _is_defined_replay_version_history_t(replay_version_history_t v);

private:
    static const std::set<replay_version_history_t> _values_replay_version_history_t;
    static std::set<replay_version_history_t> _build_values_replay_version_history_t();

public:

    fortnite_replay_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, fortnite_replay_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~fortnite_replay_t();

    /**
     * Checkpoint chunk for fast-forwarding through replay.
     * Contains actor state snapshots.
     */

    class checkpoint_chunk_t : public kaitai::kstruct {

    public:

        checkpoint_chunk_t(kaitai::kstream* p__io, fortnite_replay_t::replay_chunk_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~checkpoint_chunk_t();

    private:
        fstring_t* m_id;
        fstring_t* m_group;
        fstring_t* m_metadata;
        uint32_t m_start_time;
        uint32_t m_end_time;
        int32_t m_size_in_bytes;
        std::string m_data;
        fortnite_replay_t* m__root;
        fortnite_replay_t::replay_chunk_t* m__parent;

    public:

        /**
         * Checkpoint identifier
         */
        fstring_t* id() const { return m_id; }

        /**
         * Checkpoint group name
         */
        fstring_t* group() const { return m_group; }

        /**
         * Custom metadata
         */
        fstring_t* metadata() const { return m_metadata; }

        /**
         * Start time in milliseconds
         */
        uint32_t start_time() const { return m_start_time; }

        /**
         * End time in milliseconds
         */
        uint32_t end_time() const { return m_end_time; }

        /**
         * Size of checkpoint data
         */
        int32_t size_in_bytes() const { return m_size_in_bytes; }

        /**
         * Checkpoint data (may be encrypted/compressed).
         * Contains: deleted startup actors, GUID cache, net field export groups,
         * and serialized frame data.
         */
        std::string data() const { return m_data; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::replay_chunk_t* _parent() const { return m__parent; }
    };

    /**
     * Array of custom versions (GUID + version number)
     */

    class custom_version_array_t : public kaitai::kstruct {

    public:

        custom_version_array_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~custom_version_array_t();

    private:
        int32_t m_count;
        std::vector<custom_version_entry_t*>* m_entries;
        fortnite_replay_t* m__root;
        kaitai::kstruct* m__parent;

    public:

        /**
         * Number of custom versions
         */
        int32_t count() const { return m_count; }
        std::vector<custom_version_entry_t*>* entries() const { return m_entries; }
        fortnite_replay_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    /**
     * A single custom version entry (20 bytes total)
     */

    class custom_version_entry_t : public kaitai::kstruct {

    public:

        custom_version_entry_t(kaitai::kstream* p__io, fortnite_replay_t::custom_version_array_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~custom_version_entry_t();

    private:
        std::string m_guid;
        int32_t m_version;
        fortnite_replay_t* m__root;
        fortnite_replay_t::custom_version_array_t* m__parent;

    public:

        /**
         * Version GUID
         */
        std::string guid() const { return m_guid; }

        /**
         * Version number
         */
        int32_t version() const { return m_version; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::custom_version_array_t* _parent() const { return m__parent; }
    };

    /**
     * Full engine version information
     */

    class engine_version_full_t : public kaitai::kstruct {

    public:

        engine_version_full_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~engine_version_full_t();

    private:
        uint16_t m_major;
        uint16_t m_minor;
        uint16_t m_patch;
        uint32_t m_changelist;
        fstring_t* m_branch;
        fortnite_replay_t* m__root;
        fortnite_replay_t::header_chunk_t* m__parent;

    public:

        /**
         * Major version number
         */
        uint16_t major() const { return m_major; }

        /**
         * Minor version number
         */
        uint16_t minor() const { return m_minor; }

        /**
         * Patch version number
         */
        uint16_t patch() const { return m_patch; }

        /**
         * Engine changelist
         */
        uint32_t changelist() const { return m_changelist; }

        /**
         * Branch name string
         */
        fstring_t* branch() const { return m_branch; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::header_chunk_t* _parent() const { return m__parent; }
    };

    /**
     * Custom event chunk for game-specific events (kills, stats, etc.)
     */

    class event_chunk_t : public kaitai::kstruct {

    public:

        event_chunk_t(kaitai::kstream* p__io, fortnite_replay_t::replay_chunk_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~event_chunk_t();

    private:
        fstring_t* m_id;
        fstring_t* m_group;
        fstring_t* m_metadata;
        uint32_t m_start_time;
        uint32_t m_end_time;
        int32_t m_size_in_bytes;
        std::string m_data;
        fortnite_replay_t* m__root;
        fortnite_replay_t::replay_chunk_t* m__parent;

    public:

        /**
         * Event identifier
         */
        fstring_t* id() const { return m_id; }

        /**
         * Event group name
         */
        fstring_t* group() const { return m_group; }

        /**
         * Custom metadata
         */
        fstring_t* metadata() const { return m_metadata; }

        /**
         * Event start time in milliseconds
         */
        uint32_t start_time() const { return m_start_time; }

        /**
         * Event end time in milliseconds
         */
        uint32_t end_time() const { return m_end_time; }

        /**
         * Size of event data
         */
        int32_t size_in_bytes() const { return m_size_in_bytes; }

        /**
         * Event-specific binary data
         */
        std::string data() const { return m_data; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::replay_chunk_t* _parent() const { return m__parent; }
    };

    /**
     * Unreal Engine FString serialization.
     * Length is signed: positive = ASCII/UTF-8, negative = UTF-16 (abs(len) * 2 bytes)
     */

    class fstring_t : public kaitai::kstruct {

    public:

        fstring_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~fstring_t();

    private:
        int32_t m_length;
        std::string m_value_ascii;
        bool n_value_ascii;

    public:
        bool _is_null_value_ascii() { value_ascii(); return n_value_ascii; };

    private:
        std::string m_value_unicode;
        bool n_value_unicode;

    public:
        bool _is_null_value_unicode() { value_unicode(); return n_value_unicode; };

    private:
        fortnite_replay_t* m__root;
        kaitai::kstruct* m__parent;

    public:

        /**
         * String length (negative for Unicode)
         */
        int32_t length() const { return m_length; }

        /**
         * ASCII/UTF-8 string data (including null terminator)
         */
        std::string value_ascii() const { return m_value_ascii; }

        /**
         * Unicode string data (including null terminator)
         */
        std::string value_unicode() const { return m_value_unicode; }
        fortnite_replay_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    /**
     * Array of FStrings
     */

    class fstring_array_t : public kaitai::kstruct {

    public:

        fstring_array_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~fstring_array_t();

    private:
        uint32_t m_count;
        std::vector<fstring_t*>* m_entries;
        fortnite_replay_t* m__root;
        fortnite_replay_t::header_chunk_t* m__parent;

    public:

        /**
         * Number of strings
         */
        uint32_t count() const { return m_count; }
        std::vector<fstring_t*>* entries() const { return m_entries; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::header_chunk_t* _parent() const { return m__parent; }
    };

    /**
     * Network header chunk containing version information.
     * See DemoNetDriver.h line 191
     */

    class header_chunk_t : public kaitai::kstruct {

    public:

        header_chunk_t(kaitai::kstream* p__io, fortnite_replay_t::replay_chunk_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~header_chunk_t();

    private:
        std::string m_magic;
        network_version_history_t m_network_version;
        custom_version_array_t* m_custom_versions;
        bool n_custom_versions;

    public:
        bool _is_null_custom_versions() { custom_versions(); return n_custom_versions; };

    private:
        uint32_t m_network_checksum;
        engine_network_version_history_t m_engine_network_version;
        uint32_t m_game_network_protocol_version;
        std::string m_guid;
        bool n_guid;

    public:
        bool _is_null_guid() { guid(); return n_guid; };

    private:
        engine_version_full_t* m_version_full;
        bool n_version_full;

    public:
        bool _is_null_version_full() { version_full(); return n_version_full; };

    private:
        uint32_t m_changelist_legacy;
        bool n_changelist_legacy;

    public:
        bool _is_null_changelist_legacy() { changelist_legacy(); return n_changelist_legacy; };

    private:
        recording_metadata_t* m_recording_metadata;
        bool n_recording_metadata;

    public:
        bool _is_null_recording_metadata() { recording_metadata(); return n_recording_metadata; };

    private:
        level_names_and_times_array_t* m_level_names_and_times;
        uint32_t m_flags;
        bool n_flags;

    public:
        bool _is_null_flags() { flags(); return n_flags; };

    private:
        fstring_array_t* m_game_specific_data;
        package_version_info_t* m_package_version_info;
        bool n_package_version_info;

    public:
        bool _is_null_package_version_info() { package_version_info(); return n_package_version_info; };

    private:
        fortnite_replay_t* m__root;
        fortnite_replay_t::replay_chunk_t* m__parent;

    public:

        /**
         * Network magic number 0x2CF5A13D (little-endian)
         */
        std::string magic() const { return m_magic; }

        /**
         * Network version history
         */
        network_version_history_t network_version() const { return m_network_version; }

        /**
         * Custom version information
         */
        custom_version_array_t* custom_versions() const { return m_custom_versions; }

        /**
         * Network checksum for compatibility
         */
        uint32_t network_checksum() const { return m_network_checksum; }

        /**
         * Engine network version
         */
        engine_network_version_history_t engine_network_version() const { return m_engine_network_version; }

        /**
         * Game-specific network protocol version
         */
        uint32_t game_network_protocol_version() const { return m_game_network_protocol_version; }

        /**
         * Unique replay GUID (16 bytes)
         */
        std::string guid() const { return m_guid; }

        /**
         * Full engine version info
         */
        engine_version_full_t* version_full() const { return m_version_full; }

        /**
         * Changelist (legacy format)
         */
        uint32_t changelist_legacy() const { return m_changelist_legacy; }

        /**
         * Recording metadata (UE4/UE5 version info)
         */
        recording_metadata_t* recording_metadata() const { return m_recording_metadata; }

        /**
         * Array of level names with their times
         */
        level_names_and_times_array_t* level_names_and_times() const { return m_level_names_and_times; }

        /**
         * Replay header flags (bitmask)
         */
        uint32_t flags() const { return m_flags; }

        /**
         * Game-specific data strings
         */
        fstring_array_t* game_specific_data() const { return m_game_specific_data; }

        /**
         * Package version and platform info
         */
        package_version_info_t* package_version_info() const { return m_package_version_info; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::replay_chunk_t* _parent() const { return m__parent; }
    };

    /**
     * Level name with its time offset
     */

    class level_name_and_time_t : public kaitai::kstruct {

    public:

        level_name_and_time_t(kaitai::kstream* p__io, fortnite_replay_t::level_names_and_times_array_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~level_name_and_time_t();

    private:
        fstring_t* m_name;
        uint32_t m_time;
        fortnite_replay_t* m__root;
        fortnite_replay_t::level_names_and_times_array_t* m__parent;

    public:

        /**
         * Level name/path
         */
        fstring_t* name() const { return m_name; }

        /**
         * Time offset in milliseconds
         */
        uint32_t time() const { return m_time; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::level_names_and_times_array_t* _parent() const { return m__parent; }
    };

    /**
     * Array of level names with their associated times
     */

    class level_names_and_times_array_t : public kaitai::kstruct {

    public:

        level_names_and_times_array_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~level_names_and_times_array_t();

    private:
        uint32_t m_count;
        std::vector<level_name_and_time_t*>* m_entries;
        fortnite_replay_t* m__root;
        fortnite_replay_t::header_chunk_t* m__parent;

    public:

        /**
         * Number of levels
         */
        uint32_t count() const { return m_count; }
        std::vector<level_name_and_time_t*>* entries() const { return m_entries; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::header_chunk_t* _parent() const { return m__parent; }
    };

    /**
     * Package version and platform information
     */

    class package_version_info_t : public kaitai::kstruct {

    public:

        package_version_info_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~package_version_info_t();

    private:
        float m_min_record_hz;
        float m_max_record_hz;
        float m_frame_limit_in_ms;
        float m_checkpoint_limit_in_ms;
        fstring_t* m_platform;
        uint8_t m_build_config;
        build_target_type_t m_build_target_type;
        fortnite_replay_t* m__root;
        fortnite_replay_t::header_chunk_t* m__parent;

    public:

        /**
         * Minimum recording rate in Hz
         */
        float min_record_hz() const { return m_min_record_hz; }

        /**
         * Maximum recording rate in Hz
         */
        float max_record_hz() const { return m_max_record_hz; }

        /**
         * Frame limit in milliseconds
         */
        float frame_limit_in_ms() const { return m_frame_limit_in_ms; }

        /**
         * Checkpoint limit in milliseconds
         */
        float checkpoint_limit_in_ms() const { return m_checkpoint_limit_in_ms; }

        /**
         * Platform name (e.g., "Windows")
         */
        fstring_t* platform() const { return m_platform; }

        /**
         * Build configuration
         */
        uint8_t build_config() const { return m_build_config; }

        /**
         * Build target type
         */
        build_target_type_t build_target_type() const { return m_build_target_type; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::header_chunk_t* _parent() const { return m__parent; }
    };

    /**
     * Recording metadata for UE4/UE5 version info
     */

    class recording_metadata_t : public kaitai::kstruct {

    public:

        recording_metadata_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~recording_metadata_t();

    private:
        uint32_t m_ue4_version;
        uint32_t m_ue5_version;
        uint32_t m_package_version_licensee_ue;
        fortnite_replay_t* m__root;
        fortnite_replay_t::header_chunk_t* m__parent;

    public:

        /**
         * UE4 package file version
         */
        uint32_t ue4_version() const { return m_ue4_version; }

        /**
         * UE5 package file version
         */
        uint32_t ue5_version() const { return m_ue5_version; }

        /**
         * Licensee UE package version
         */
        uint32_t package_version_licensee_ue() const { return m_package_version_licensee_ue; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::header_chunk_t* _parent() const { return m__parent; }
    };

    /**
     * A chunk in the replay file. The file consists of multiple chunks
     * of different types containing headers, replay data, checkpoints, and events.
     */

    class replay_chunk_t : public kaitai::kstruct {

    public:

        replay_chunk_t(kaitai::kstream* p__io, fortnite_replay_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~replay_chunk_t();

    private:
        replay_chunk_type_t m_chunk_type;
        int32_t m_chunk_size;
        kaitai::kstruct* m_chunk_data;
        bool n_chunk_data;

    public:
        bool _is_null_chunk_data() { chunk_data(); return n_chunk_data; };

    private:
        fortnite_replay_t* m__root;
        fortnite_replay_t* m__parent;
        std::string m__raw_chunk_data;
        kaitai::kstream* m__io__raw_chunk_data;

    public:

        /**
         * Type of this chunk
         */
        replay_chunk_type_t chunk_type() const { return m_chunk_type; }

        /**
         * Size of chunk data in bytes
         */
        int32_t chunk_size() const { return m_chunk_size; }

        /**
         * Chunk payload (may be encrypted/compressed)
         */
        kaitai::kstruct* chunk_data() const { return m_chunk_data; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t* _parent() const { return m__parent; }
        std::string _raw_chunk_data() const { return m__raw_chunk_data; }
        kaitai::kstream* _io__raw_chunk_data() const { return m__io__raw_chunk_data; }
    };

    /**
     * Replay data chunk containing recorded network frames.
     * Data may be compressed and/or encrypted based on replay_info flags.
     */

    class replay_data_chunk_t : public kaitai::kstruct {

    public:

        replay_data_chunk_t(kaitai::kstream* p__io, fortnite_replay_t::replay_chunk_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~replay_data_chunk_t();

    private:
        uint32_t m_start_time;
        bool n_start_time;

    public:
        bool _is_null_start_time() { start_time(); return n_start_time; };

    private:
        uint32_t m_end_time;
        bool n_end_time;

    public:
        bool _is_null_end_time() { end_time(); return n_end_time; };

    private:
        uint32_t m_data_length;
        bool n_data_length;

    public:
        bool _is_null_data_length() { data_length(); return n_data_length; };

    private:
        int32_t m_memory_size_in_bytes;
        bool n_memory_size_in_bytes;

    public:
        bool _is_null_memory_size_in_bytes() { memory_size_in_bytes(); return n_memory_size_in_bytes; };

    private:
        std::string m_data;
        fortnite_replay_t* m__root;
        fortnite_replay_t::replay_chunk_t* m__parent;

    public:

        /**
         * Start time in milliseconds
         */
        uint32_t start_time() const { return m_start_time; }

        /**
         * End time in milliseconds
         */
        uint32_t end_time() const { return m_end_time; }

        /**
         * Length of the following data
         */
        uint32_t data_length() const { return m_data_length; }

        /**
         * Memory size when decompressed
         */
        int32_t memory_size_in_bytes() const { return m_memory_size_in_bytes; }

        /**
         * Replay frame data. If compressed, starts with decompressed_size (u4),
         * compressed_size (u4), then compressed bytes. Contains demo frames
         * with network packets.
         */
        std::string data() const { return m_data; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t::replay_chunk_t* _parent() const { return m__parent; }
    };

    /**
     * File header containing replay metadata.
     * See LocalFileNetworkReplayStreaming.cpp line 183
     */

    class replay_info_t : public kaitai::kstruct {

    public:

        replay_info_t(kaitai::kstream* p__io, fortnite_replay_t* p__parent = 0, fortnite_replay_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~replay_info_t();

    private:
        std::string m_magic;
        replay_version_history_t m_file_version;
        custom_version_array_t* m_custom_versions;
        bool n_custom_versions;

    public:
        bool _is_null_custom_versions() { custom_versions(); return n_custom_versions; };

    private:
        uint32_t m_length_in_ms;
        uint32_t m_network_version;
        uint32_t m_changelist;
        fstring_t* m_friendly_name;
        uint32_t m_is_live;
        int64_t m_timestamp;
        bool n_timestamp;

    public:
        bool _is_null_timestamp() { timestamp(); return n_timestamp; };

    private:
        uint32_t m_is_compressed;
        bool n_is_compressed;

    public:
        bool _is_null_is_compressed() { is_compressed(); return n_is_compressed; };

    private:
        uint32_t m_is_encrypted;
        bool n_is_encrypted;

    public:
        bool _is_null_is_encrypted() { is_encrypted(); return n_is_encrypted; };

    private:
        uint32_t m_encryption_key_size;
        bool n_encryption_key_size;

    public:
        bool _is_null_encryption_key_size() { encryption_key_size(); return n_encryption_key_size; };

    private:
        std::string m_encryption_key;
        bool n_encryption_key;

    public:
        bool _is_null_encryption_key() { encryption_key(); return n_encryption_key; };

    private:
        fortnite_replay_t* m__root;
        fortnite_replay_t* m__parent;

    public:

        /**
         * File magic number 0x1CA2E27F (little-endian)
         */
        std::string magic() const { return m_magic; }

        /**
         * Replay file format version
         */
        replay_version_history_t file_version() const { return m_file_version; }

        /**
         * Custom version information
         */
        custom_version_array_t* custom_versions() const { return m_custom_versions; }

        /**
         * Total replay duration in milliseconds
         */
        uint32_t length_in_ms() const { return m_length_in_ms; }

        /**
         * Network protocol version
         */
        uint32_t network_version() const { return m_network_version; }

        /**
         * Engine changelist number
         */
        uint32_t changelist() const { return m_changelist; }

        /**
         * Human-readable replay name
         */
        fstring_t* friendly_name() const { return m_friendly_name; }

        /**
         * Whether the replay is still being recorded (1=true, 0=false)
         */
        uint32_t is_live() const { return m_is_live; }

        /**
         * Recording timestamp as .NET DateTime binary format
         */
        int64_t timestamp() const { return m_timestamp; }

        /**
         * Whether chunk data is compressed (1=true, 0=false)
         */
        uint32_t is_compressed() const { return m_is_compressed; }

        /**
         * Whether chunk data is encrypted (1=true, 0=false)
         */
        uint32_t is_encrypted() const { return m_is_encrypted; }

        /**
         * Size of encryption key in bytes
         */
        uint32_t encryption_key_size() const { return m_encryption_key_size; }

        /**
         * AES encryption key
         */
        std::string encryption_key() const { return m_encryption_key; }
        fortnite_replay_t* _root() const { return m__root; }
        fortnite_replay_t* _parent() const { return m__parent; }
    };

private:
    replay_info_t* m_replay_info;
    std::vector<replay_chunk_t*>* m_chunks;
    fortnite_replay_t* m__root;
    kaitai::kstruct* m__parent;

public:
    replay_info_t* replay_info() const { return m_replay_info; }
    std::vector<replay_chunk_t*>* chunks() const { return m_chunks; }
    fortnite_replay_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // FORTNITE_REPLAY_H_
