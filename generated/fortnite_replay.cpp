// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "fortnite_replay.h"
#include "kaitai/exceptions.h"
std::set<fortnite_replay_t::build_target_type_t> fortnite_replay_t::_build_values_build_target_type_t() {
    std::set<fortnite_replay_t::build_target_type_t> _t;
    _t.insert(fortnite_replay_t::BUILD_TARGET_TYPE_UNKNOWN);
    _t.insert(fortnite_replay_t::BUILD_TARGET_TYPE_GAME);
    _t.insert(fortnite_replay_t::BUILD_TARGET_TYPE_SERVER);
    _t.insert(fortnite_replay_t::BUILD_TARGET_TYPE_CLIENT);
    _t.insert(fortnite_replay_t::BUILD_TARGET_TYPE_EDITOR);
    _t.insert(fortnite_replay_t::BUILD_TARGET_TYPE_PROGRAM);
    return _t;
}
const std::set<fortnite_replay_t::build_target_type_t> fortnite_replay_t::_values_build_target_type_t = fortnite_replay_t::_build_values_build_target_type_t();
bool fortnite_replay_t::_is_defined_build_target_type_t(fortnite_replay_t::build_target_type_t v) {
    return fortnite_replay_t::_values_build_target_type_t.find(v) != fortnite_replay_t::_values_build_target_type_t.end();
}
std::set<fortnite_replay_t::engine_network_version_history_t> fortnite_replay_t::_build_values_engine_network_version_history_t() {
    std::set<fortnite_replay_t::engine_network_version_history_t> _t;
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_INITIAL);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_REPLAY_BACKWARDS_COMPAT);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_MAX_ACTOR_CHANNELS_CUSTOMIZATION);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_REPCMD_CHECKSUM_REMOVE_PRINTF);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_NEW_ACTOR_OVERRIDE_LEVEL);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_CHANNEL_NAMES);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_CHANNEL_CLOSE_REASON);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_ACKS_INCLUDED_IN_HEADER);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_NETEXPORT_SERIALIZATION);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_NETEXPORT_SERIALIZE_FIX);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_FAST_ARRAY_DELTA_STRUCT);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_FIX_ENUM_SERIALIZATION);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_OPTIONALLY_QUANTIZE_SPAWN_INFO);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_JITTER_IN_HEADER);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_CLASSNETCACHE_FULLNAME);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_REPLAY_DORMANCY);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_ENUM_SERIALIZATION_COMPAT);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_SUBOBJECT_OUTER_CHAIN);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_HITRESULT_INSTANCEHANDLE);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_INTERFACE_PROPERTY_SERIALIZATION);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_MONTAGE_PLAY_INST_ID_SERIALIZATION);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_SERIALIZE_DOUBLE_VECTORS_AS_DOUBLES);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_PACKED_VECTOR_LWC_SUPPORT);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_PAWN_REMOTEVIEWPITCH);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_REPMOVE_SERVERFRAME_AND_HANDLE);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_21_AND_VIEWPITCH_ONLY_DO_NOT_USE);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_PLACEHOLDER);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_RUNTIME_FEATURES_COMPATIBILITY);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_SOFTOBJECTPTR_NETGUIDS);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_SUBOBJECT_DESTROY_FLAG);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_GAMESTATE_REPLICATED_TIME_AS_DOUBLE);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_HISTORY_CUSTOMVERSION);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_DYNAMIC_MONTAGE_SERIALIZATION);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_PREDICTION_KEY_BASE_NOT_REPLICATED);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_REP_MOVE_OPTIONAL_ACCELERATION);
    _t.insert(fortnite_replay_t::ENGINE_NETWORK_VERSION_HISTORY_CUSTOM_EXPORTS);
    return _t;
}
const std::set<fortnite_replay_t::engine_network_version_history_t> fortnite_replay_t::_values_engine_network_version_history_t = fortnite_replay_t::_build_values_engine_network_version_history_t();
bool fortnite_replay_t::_is_defined_engine_network_version_history_t(fortnite_replay_t::engine_network_version_history_t v) {
    return fortnite_replay_t::_values_engine_network_version_history_t.find(v) != fortnite_replay_t::_values_engine_network_version_history_t.end();
}
std::set<fortnite_replay_t::network_version_history_t> fortnite_replay_t::_build_values_network_version_history_t() {
    std::set<fortnite_replay_t::network_version_history_t> _t;
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_REPLAY_INITIAL);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_SAVE_ABS_TIME_MS);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_INCREASE_BUFFER);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_SAVE_ENGINE_VERSION);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_EXTRA_VERSION);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_MULTIPLE_LEVELS);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_MULTIPLE_LEVELS_TIME_CHANGES);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_DELETED_STARTUP_ACTORS);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_HEADER_FLAGS);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_LEVEL_STREAMING_FIXES);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_SAVE_FULL_ENGINE_VERSION);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_HEADER_GUID);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_CHARACTER_MOVEMENT);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_CHARACTER_MOVEMENT_NOINTERP);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_GUID_NAMETABLE);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_GUIDCACHE_CHECKSUMS);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_SAVE_PACKAGE_VERSION_UE);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_RECORDING_METADATA);
    _t.insert(fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_USE_CUSTOM_VERSION);
    return _t;
}
const std::set<fortnite_replay_t::network_version_history_t> fortnite_replay_t::_values_network_version_history_t = fortnite_replay_t::_build_values_network_version_history_t();
bool fortnite_replay_t::_is_defined_network_version_history_t(fortnite_replay_t::network_version_history_t v) {
    return fortnite_replay_t::_values_network_version_history_t.find(v) != fortnite_replay_t::_values_network_version_history_t.end();
}
std::set<fortnite_replay_t::replay_chunk_type_t> fortnite_replay_t::_build_values_replay_chunk_type_t() {
    std::set<fortnite_replay_t::replay_chunk_type_t> _t;
    _t.insert(fortnite_replay_t::REPLAY_CHUNK_TYPE_HEADER);
    _t.insert(fortnite_replay_t::REPLAY_CHUNK_TYPE_REPLAY_DATA);
    _t.insert(fortnite_replay_t::REPLAY_CHUNK_TYPE_CHECKPOINT);
    _t.insert(fortnite_replay_t::REPLAY_CHUNK_TYPE_EVENT);
    _t.insert(fortnite_replay_t::REPLAY_CHUNK_TYPE_UNKNOWN);
    return _t;
}
const std::set<fortnite_replay_t::replay_chunk_type_t> fortnite_replay_t::_values_replay_chunk_type_t = fortnite_replay_t::_build_values_replay_chunk_type_t();
bool fortnite_replay_t::_is_defined_replay_chunk_type_t(fortnite_replay_t::replay_chunk_type_t v) {
    return fortnite_replay_t::_values_replay_chunk_type_t.find(v) != fortnite_replay_t::_values_replay_chunk_type_t.end();
}
std::set<fortnite_replay_t::replay_header_flags_t> fortnite_replay_t::_build_values_replay_header_flags_t() {
    std::set<fortnite_replay_t::replay_header_flags_t> _t;
    _t.insert(fortnite_replay_t::REPLAY_HEADER_FLAGS_NONE);
    _t.insert(fortnite_replay_t::REPLAY_HEADER_FLAGS_CLIENT_RECORDED);
    _t.insert(fortnite_replay_t::REPLAY_HEADER_FLAGS_HAS_STREAMING_FIXES);
    _t.insert(fortnite_replay_t::REPLAY_HEADER_FLAGS_DELTA_CHECKPOINTS);
    _t.insert(fortnite_replay_t::REPLAY_HEADER_FLAGS_GAME_SPECIFIC_FRAME_DATA);
    _t.insert(fortnite_replay_t::REPLAY_HEADER_FLAGS_REPLAY_CONNECTION);
    _t.insert(fortnite_replay_t::REPLAY_HEADER_FLAGS_ACTOR_PRIORITIZATION_ENABLED);
    _t.insert(fortnite_replay_t::REPLAY_HEADER_FLAGS_NET_RELEVANCY_ENABLED);
    _t.insert(fortnite_replay_t::REPLAY_HEADER_FLAGS_ASYNC_RECORDED);
    return _t;
}
const std::set<fortnite_replay_t::replay_header_flags_t> fortnite_replay_t::_values_replay_header_flags_t = fortnite_replay_t::_build_values_replay_header_flags_t();
bool fortnite_replay_t::_is_defined_replay_header_flags_t(fortnite_replay_t::replay_header_flags_t v) {
    return fortnite_replay_t::_values_replay_header_flags_t.find(v) != fortnite_replay_t::_values_replay_header_flags_t.end();
}
std::set<fortnite_replay_t::replay_version_history_t> fortnite_replay_t::_build_values_replay_version_history_t() {
    std::set<fortnite_replay_t::replay_version_history_t> _t;
    _t.insert(fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_INITIAL);
    _t.insert(fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_FIXEDSIZE_FRIENDLY_NAME);
    _t.insert(fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_COMPRESSION);
    _t.insert(fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_RECORDED_TIMESTAMP);
    _t.insert(fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_STREAM_CHUNK_TIMES);
    _t.insert(fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_FRIENDLY_NAME_ENCODING);
    _t.insert(fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_ENCRYPTION);
    _t.insert(fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_CUSTOM_VERSIONS);
    return _t;
}
const std::set<fortnite_replay_t::replay_version_history_t> fortnite_replay_t::_values_replay_version_history_t = fortnite_replay_t::_build_values_replay_version_history_t();
bool fortnite_replay_t::_is_defined_replay_version_history_t(fortnite_replay_t::replay_version_history_t v) {
    return fortnite_replay_t::_values_replay_version_history_t.find(v) != fortnite_replay_t::_values_replay_version_history_t.end();
}

fortnite_replay_t::fortnite_replay_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root ? p__root : this;
    m_replay_info = 0;
    m_chunks = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::_read() {
    m_replay_info = new replay_info_t(m__io, this, m__root);
    m_chunks = new std::vector<replay_chunk_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_chunks->push_back(new replay_chunk_t(m__io, this, m__root));
            i++;
        }
    }
}

fortnite_replay_t::~fortnite_replay_t() {
    _clean_up();
}

void fortnite_replay_t::_clean_up() {
    if (m_replay_info) {
        delete m_replay_info; m_replay_info = 0;
    }
    if (m_chunks) {
        for (std::vector<replay_chunk_t*>::iterator it = m_chunks->begin(); it != m_chunks->end(); ++it) {
            delete *it;
        }
        delete m_chunks; m_chunks = 0;
    }
}

fortnite_replay_t::checkpoint_chunk_t::checkpoint_chunk_t(kaitai::kstream* p__io, fortnite_replay_t::replay_chunk_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_id = 0;
    m_group = 0;
    m_metadata = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::checkpoint_chunk_t::_read() {
    m_id = new fstring_t(m__io, this, m__root);
    m_group = new fstring_t(m__io, this, m__root);
    m_metadata = new fstring_t(m__io, this, m__root);
    m_start_time = m__io->read_u4le();
    m_end_time = m__io->read_u4le();
    m_size_in_bytes = m__io->read_s4le();
    m_data = m__io->read_bytes(size_in_bytes());
}

fortnite_replay_t::checkpoint_chunk_t::~checkpoint_chunk_t() {
    _clean_up();
}

void fortnite_replay_t::checkpoint_chunk_t::_clean_up() {
    if (m_id) {
        delete m_id; m_id = 0;
    }
    if (m_group) {
        delete m_group; m_group = 0;
    }
    if (m_metadata) {
        delete m_metadata; m_metadata = 0;
    }
}

fortnite_replay_t::custom_version_array_t::custom_version_array_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_entries = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::custom_version_array_t::_read() {
    m_count = m__io->read_s4le();
    m_entries = new std::vector<custom_version_entry_t*>();
    const int l_entries = count();
    for (int i = 0; i < l_entries; i++) {
        m_entries->push_back(new custom_version_entry_t(m__io, this, m__root));
    }
}

fortnite_replay_t::custom_version_array_t::~custom_version_array_t() {
    _clean_up();
}

void fortnite_replay_t::custom_version_array_t::_clean_up() {
    if (m_entries) {
        for (std::vector<custom_version_entry_t*>::iterator it = m_entries->begin(); it != m_entries->end(); ++it) {
            delete *it;
        }
        delete m_entries; m_entries = 0;
    }
}

fortnite_replay_t::custom_version_entry_t::custom_version_entry_t(kaitai::kstream* p__io, fortnite_replay_t::custom_version_array_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::custom_version_entry_t::_read() {
    m_guid = m__io->read_bytes(16);
    m_version = m__io->read_s4le();
}

fortnite_replay_t::custom_version_entry_t::~custom_version_entry_t() {
    _clean_up();
}

void fortnite_replay_t::custom_version_entry_t::_clean_up() {
}

fortnite_replay_t::engine_version_full_t::engine_version_full_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_branch = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::engine_version_full_t::_read() {
    m_major = m__io->read_u2le();
    m_minor = m__io->read_u2le();
    m_patch = m__io->read_u2le();
    m_changelist = m__io->read_u4le();
    m_branch = new fstring_t(m__io, this, m__root);
}

fortnite_replay_t::engine_version_full_t::~engine_version_full_t() {
    _clean_up();
}

void fortnite_replay_t::engine_version_full_t::_clean_up() {
    if (m_branch) {
        delete m_branch; m_branch = 0;
    }
}

fortnite_replay_t::event_chunk_t::event_chunk_t(kaitai::kstream* p__io, fortnite_replay_t::replay_chunk_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_id = 0;
    m_group = 0;
    m_metadata = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::event_chunk_t::_read() {
    m_id = new fstring_t(m__io, this, m__root);
    m_group = new fstring_t(m__io, this, m__root);
    m_metadata = new fstring_t(m__io, this, m__root);
    m_start_time = m__io->read_u4le();
    m_end_time = m__io->read_u4le();
    m_size_in_bytes = m__io->read_s4le();
    m_data = m__io->read_bytes(size_in_bytes());
}

fortnite_replay_t::event_chunk_t::~event_chunk_t() {
    _clean_up();
}

void fortnite_replay_t::event_chunk_t::_clean_up() {
    if (m_id) {
        delete m_id; m_id = 0;
    }
    if (m_group) {
        delete m_group; m_group = 0;
    }
    if (m_metadata) {
        delete m_metadata; m_metadata = 0;
    }
}

fortnite_replay_t::fstring_t::fstring_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::fstring_t::_read() {
    m_length = m__io->read_s4le();
    n_value_ascii = true;
    if (length() > 0) {
        n_value_ascii = false;
        m_value_ascii = kaitai::kstream::bytes_to_str(m__io->read_bytes(length()), "UTF-8");
    }
    n_value_unicode = true;
    if (length() < 0) {
        n_value_unicode = false;
        m_value_unicode = kaitai::kstream::bytes_to_str(m__io->read_bytes(-(length()) * 2), "UTF-16LE");
    }
}

fortnite_replay_t::fstring_t::~fstring_t() {
    _clean_up();
}

void fortnite_replay_t::fstring_t::_clean_up() {
    if (!n_value_ascii) {
    }
    if (!n_value_unicode) {
    }
}

fortnite_replay_t::fstring_array_t::fstring_array_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_entries = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::fstring_array_t::_read() {
    m_count = m__io->read_u4le();
    m_entries = new std::vector<fstring_t*>();
    const int l_entries = count();
    for (int i = 0; i < l_entries; i++) {
        m_entries->push_back(new fstring_t(m__io, this, m__root));
    }
}

fortnite_replay_t::fstring_array_t::~fstring_array_t() {
    _clean_up();
}

void fortnite_replay_t::fstring_array_t::_clean_up() {
    if (m_entries) {
        for (std::vector<fstring_t*>::iterator it = m_entries->begin(); it != m_entries->end(); ++it) {
            delete *it;
        }
        delete m_entries; m_entries = 0;
    }
}

fortnite_replay_t::header_chunk_t::header_chunk_t(kaitai::kstream* p__io, fortnite_replay_t::replay_chunk_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_custom_versions = 0;
    m_version_full = 0;
    m_recording_metadata = 0;
    m_level_names_and_times = 0;
    m_game_specific_data = 0;
    m_package_version_info = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::header_chunk_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(m_magic == std::string("\x3D\xA1\xF5\x2C", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x3D\xA1\xF5\x2C", 4), m_magic, m__io, std::string("/types/header_chunk/seq/0"));
    }
    m_network_version = static_cast<fortnite_replay_t::network_version_history_t>(m__io->read_u4le());
    n_custom_versions = true;
    if (network_version() >= fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_USE_CUSTOM_VERSION) {
        n_custom_versions = false;
        m_custom_versions = new custom_version_array_t(m__io, this, m__root);
    }
    m_network_checksum = m__io->read_u4le();
    m_engine_network_version = static_cast<fortnite_replay_t::engine_network_version_history_t>(m__io->read_u4le());
    m_game_network_protocol_version = m__io->read_u4le();
    n_guid = true;
    if (network_version() >= fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_HEADER_GUID) {
        n_guid = false;
        m_guid = m__io->read_bytes(16);
    }
    n_version_full = true;
    if (network_version() >= fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_SAVE_FULL_ENGINE_VERSION) {
        n_version_full = false;
        m_version_full = new engine_version_full_t(m__io, this, m__root);
    }
    n_changelist_legacy = true;
    if (network_version() < fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_SAVE_FULL_ENGINE_VERSION) {
        n_changelist_legacy = false;
        m_changelist_legacy = m__io->read_u4le();
    }
    n_recording_metadata = true;
    if (network_version() >= fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_RECORDING_METADATA) {
        n_recording_metadata = false;
        m_recording_metadata = new recording_metadata_t(m__io, this, m__root);
    }
    m_level_names_and_times = new level_names_and_times_array_t(m__io, this, m__root);
    n_flags = true;
    if (network_version() >= fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_HEADER_FLAGS) {
        n_flags = false;
        m_flags = m__io->read_u4le();
    }
    m_game_specific_data = new fstring_array_t(m__io, this, m__root);
    n_package_version_info = true;
    if (network_version() >= fortnite_replay_t::NETWORK_VERSION_HISTORY_HISTORY_SAVE_PACKAGE_VERSION_UE) {
        n_package_version_info = false;
        m_package_version_info = new package_version_info_t(m__io, this, m__root);
    }
}

fortnite_replay_t::header_chunk_t::~header_chunk_t() {
    _clean_up();
}

void fortnite_replay_t::header_chunk_t::_clean_up() {
    if (!n_custom_versions) {
        if (m_custom_versions) {
            delete m_custom_versions; m_custom_versions = 0;
        }
    }
    if (!n_guid) {
    }
    if (!n_version_full) {
        if (m_version_full) {
            delete m_version_full; m_version_full = 0;
        }
    }
    if (!n_changelist_legacy) {
    }
    if (!n_recording_metadata) {
        if (m_recording_metadata) {
            delete m_recording_metadata; m_recording_metadata = 0;
        }
    }
    if (m_level_names_and_times) {
        delete m_level_names_and_times; m_level_names_and_times = 0;
    }
    if (!n_flags) {
    }
    if (m_game_specific_data) {
        delete m_game_specific_data; m_game_specific_data = 0;
    }
    if (!n_package_version_info) {
        if (m_package_version_info) {
            delete m_package_version_info; m_package_version_info = 0;
        }
    }
}

fortnite_replay_t::level_name_and_time_t::level_name_and_time_t(kaitai::kstream* p__io, fortnite_replay_t::level_names_and_times_array_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::level_name_and_time_t::_read() {
    m_name = new fstring_t(m__io, this, m__root);
    m_time = m__io->read_u4le();
}

fortnite_replay_t::level_name_and_time_t::~level_name_and_time_t() {
    _clean_up();
}

void fortnite_replay_t::level_name_and_time_t::_clean_up() {
    if (m_name) {
        delete m_name; m_name = 0;
    }
}

fortnite_replay_t::level_names_and_times_array_t::level_names_and_times_array_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_entries = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::level_names_and_times_array_t::_read() {
    m_count = m__io->read_u4le();
    m_entries = new std::vector<level_name_and_time_t*>();
    const int l_entries = count();
    for (int i = 0; i < l_entries; i++) {
        m_entries->push_back(new level_name_and_time_t(m__io, this, m__root));
    }
}

fortnite_replay_t::level_names_and_times_array_t::~level_names_and_times_array_t() {
    _clean_up();
}

void fortnite_replay_t::level_names_and_times_array_t::_clean_up() {
    if (m_entries) {
        for (std::vector<level_name_and_time_t*>::iterator it = m_entries->begin(); it != m_entries->end(); ++it) {
            delete *it;
        }
        delete m_entries; m_entries = 0;
    }
}

fortnite_replay_t::package_version_info_t::package_version_info_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_platform = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::package_version_info_t::_read() {
    m_min_record_hz = m__io->read_f4le();
    m_max_record_hz = m__io->read_f4le();
    m_frame_limit_in_ms = m__io->read_f4le();
    m_checkpoint_limit_in_ms = m__io->read_f4le();
    m_platform = new fstring_t(m__io, this, m__root);
    m_build_config = m__io->read_u1();
    m_build_target_type = static_cast<fortnite_replay_t::build_target_type_t>(m__io->read_u1());
}

fortnite_replay_t::package_version_info_t::~package_version_info_t() {
    _clean_up();
}

void fortnite_replay_t::package_version_info_t::_clean_up() {
    if (m_platform) {
        delete m_platform; m_platform = 0;
    }
}

fortnite_replay_t::recording_metadata_t::recording_metadata_t(kaitai::kstream* p__io, fortnite_replay_t::header_chunk_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::recording_metadata_t::_read() {
    m_ue4_version = m__io->read_u4le();
    m_ue5_version = m__io->read_u4le();
    m_package_version_licensee_ue = m__io->read_u4le();
}

fortnite_replay_t::recording_metadata_t::~recording_metadata_t() {
    _clean_up();
}

void fortnite_replay_t::recording_metadata_t::_clean_up() {
}

fortnite_replay_t::replay_chunk_t::replay_chunk_t(kaitai::kstream* p__io, fortnite_replay_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m__io__raw_chunk_data = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::replay_chunk_t::_read() {
    m_chunk_type = static_cast<fortnite_replay_t::replay_chunk_type_t>(m__io->read_u4le());
    m_chunk_size = m__io->read_s4le();
    n_chunk_data = true;
    switch (chunk_type()) {
    case fortnite_replay_t::REPLAY_CHUNK_TYPE_CHECKPOINT: {
        n_chunk_data = false;
        m__raw_chunk_data = m__io->read_bytes(chunk_size());
        m__io__raw_chunk_data = new kaitai::kstream(m__raw_chunk_data);
        m_chunk_data = new checkpoint_chunk_t(m__io__raw_chunk_data, this, m__root);
        break;
    }
    case fortnite_replay_t::REPLAY_CHUNK_TYPE_EVENT: {
        n_chunk_data = false;
        m__raw_chunk_data = m__io->read_bytes(chunk_size());
        m__io__raw_chunk_data = new kaitai::kstream(m__raw_chunk_data);
        m_chunk_data = new event_chunk_t(m__io__raw_chunk_data, this, m__root);
        break;
    }
    case fortnite_replay_t::REPLAY_CHUNK_TYPE_HEADER: {
        n_chunk_data = false;
        m__raw_chunk_data = m__io->read_bytes(chunk_size());
        m__io__raw_chunk_data = new kaitai::kstream(m__raw_chunk_data);
        m_chunk_data = new header_chunk_t(m__io__raw_chunk_data, this, m__root);
        break;
    }
    case fortnite_replay_t::REPLAY_CHUNK_TYPE_REPLAY_DATA: {
        n_chunk_data = false;
        m__raw_chunk_data = m__io->read_bytes(chunk_size());
        m__io__raw_chunk_data = new kaitai::kstream(m__raw_chunk_data);
        m_chunk_data = new replay_data_chunk_t(m__io__raw_chunk_data, this, m__root);
        break;
    }
    default: {
        m__raw_chunk_data = m__io->read_bytes(chunk_size());
        break;
    }
    }
}

fortnite_replay_t::replay_chunk_t::~replay_chunk_t() {
    _clean_up();
}

void fortnite_replay_t::replay_chunk_t::_clean_up() {
    if (!n_chunk_data) {
        if (m__io__raw_chunk_data) {
            delete m__io__raw_chunk_data; m__io__raw_chunk_data = 0;
        }
        if (m_chunk_data) {
            delete m_chunk_data; m_chunk_data = 0;
        }
    }
}

fortnite_replay_t::replay_data_chunk_t::replay_data_chunk_t(kaitai::kstream* p__io, fortnite_replay_t::replay_chunk_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::replay_data_chunk_t::_read() {
    n_start_time = true;
    if (_root()->replay_info()->file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_STREAM_CHUNK_TIMES) {
        n_start_time = false;
        m_start_time = m__io->read_u4le();
    }
    n_end_time = true;
    if (_root()->replay_info()->file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_STREAM_CHUNK_TIMES) {
        n_end_time = false;
        m_end_time = m__io->read_u4le();
    }
    n_data_length = true;
    if (_root()->replay_info()->file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_STREAM_CHUNK_TIMES) {
        n_data_length = false;
        m_data_length = m__io->read_u4le();
    }
    n_memory_size_in_bytes = true;
    if (_root()->replay_info()->file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_ENCRYPTION) {
        n_memory_size_in_bytes = false;
        m_memory_size_in_bytes = m__io->read_s4le();
    }
    m_data = m__io->read_bytes_full();
}

fortnite_replay_t::replay_data_chunk_t::~replay_data_chunk_t() {
    _clean_up();
}

void fortnite_replay_t::replay_data_chunk_t::_clean_up() {
    if (!n_start_time) {
    }
    if (!n_end_time) {
    }
    if (!n_data_length) {
    }
    if (!n_memory_size_in_bytes) {
    }
}

fortnite_replay_t::replay_info_t::replay_info_t(kaitai::kstream* p__io, fortnite_replay_t* p__parent, fortnite_replay_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_custom_versions = 0;
    m_friendly_name = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void fortnite_replay_t::replay_info_t::_read() {
    m_magic = m__io->read_bytes(4);
    if (!(m_magic == std::string("\x7F\xE2\xA2\x1C", 4))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\x7F\xE2\xA2\x1C", 4), m_magic, m__io, std::string("/types/replay_info/seq/0"));
    }
    m_file_version = static_cast<fortnite_replay_t::replay_version_history_t>(m__io->read_u4le());
    n_custom_versions = true;
    if (file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_CUSTOM_VERSIONS) {
        n_custom_versions = false;
        m_custom_versions = new custom_version_array_t(m__io, this, m__root);
    }
    m_length_in_ms = m__io->read_u4le();
    m_network_version = m__io->read_u4le();
    m_changelist = m__io->read_u4le();
    m_friendly_name = new fstring_t(m__io, this, m__root);
    m_is_live = m__io->read_u4le();
    n_timestamp = true;
    if (file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_RECORDED_TIMESTAMP) {
        n_timestamp = false;
        m_timestamp = m__io->read_s8le();
    }
    n_is_compressed = true;
    if (file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_COMPRESSION) {
        n_is_compressed = false;
        m_is_compressed = m__io->read_u4le();
    }
    n_is_encrypted = true;
    if (file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_ENCRYPTION) {
        n_is_encrypted = false;
        m_is_encrypted = m__io->read_u4le();
    }
    n_encryption_key_size = true;
    if (file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_ENCRYPTION) {
        n_encryption_key_size = false;
        m_encryption_key_size = m__io->read_u4le();
    }
    n_encryption_key = true;
    if (file_version() >= fortnite_replay_t::REPLAY_VERSION_HISTORY_HISTORY_ENCRYPTION) {
        n_encryption_key = false;
        m_encryption_key = m__io->read_bytes(encryption_key_size());
    }
}

fortnite_replay_t::replay_info_t::~replay_info_t() {
    _clean_up();
}

void fortnite_replay_t::replay_info_t::_clean_up() {
    if (!n_custom_versions) {
        if (m_custom_versions) {
            delete m_custom_versions; m_custom_versions = 0;
        }
    }
    if (m_friendly_name) {
        delete m_friendly_name; m_friendly_name = 0;
    }
    if (!n_timestamp) {
    }
    if (!n_is_compressed) {
    }
    if (!n_is_encrypted) {
    }
    if (!n_encryption_key_size) {
    }
    if (!n_encryption_key) {
    }
}
