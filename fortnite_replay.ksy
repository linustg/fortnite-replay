meta:
  id: fortnite_replay
  title: Fortnite Replay File
  file-extension: replay
  endian: le
  license: MIT
  ks-version: 0.9

doc: |
  Fortnite replay file format (.replay), used by Fortnite and other UE games.

  Based on FortniteReplayDecompressor project and Unreal Engine source code.

  References:
    - https://github.com/EpicGames/UnrealEngine/blob/70bc980c6361d9a7d23f6d23ffe322a2d6ef16fb/Engine/Source/Runtime/NetworkReplayStreaming/LocalFileNetworkReplayStreaming/Private/LocalFileNetworkReplayStreaming.cpp
    - https://github.com/EpicGames/UnrealEngine/blob/811c1ce579564fa92ecc22d9b70cbe9c8a8e4b9a/Engine/Source/Runtime/Engine/Classes/Engine/DemoNetDriver.h

seq:
  - id: replay_info
    type: replay_info
  - id: chunks
    type: replay_chunk
    repeat: eos

types:
  # ============================================================================
  # Main Structures
  # ============================================================================

  replay_info:
    doc: |
      File header containing replay metadata.
      See LocalFileNetworkReplayStreaming.cpp line 183
    seq:
      - id: magic
        contents: [0x7f, 0xe2, 0xa2, 0x1c]
        doc: File magic number 0x1CA2E27F (little-endian)
      - id: file_version
        type: u4
        enum: replay_version_history
        doc: Replay file format version
      - id: custom_versions
        type: custom_version_array
        if: file_version.to_i >= replay_version_history::history_custom_versions.to_i
        doc: Custom version information
      - id: length_in_ms
        type: u4
        doc: Total replay duration in milliseconds
      - id: network_version
        type: u4
        doc: Network protocol version
      - id: changelist
        type: u4
        doc: Engine changelist number
      - id: friendly_name
        type: fstring
        doc: Human-readable replay name
      - id: is_live
        type: u4
        doc: Whether the replay is still being recorded (1=true, 0=false)
      - id: timestamp
        type: s8
        if: file_version.to_i >= replay_version_history::history_recorded_timestamp.to_i
        doc: Recording timestamp as .NET DateTime binary format
      - id: is_compressed
        type: u4
        if: file_version.to_i >= replay_version_history::history_compression.to_i
        doc: Whether chunk data is compressed (1=true, 0=false)
      - id: is_encrypted
        type: u4
        if: file_version.to_i >= replay_version_history::history_encryption.to_i
        doc: Whether chunk data is encrypted (1=true, 0=false)
      - id: encryption_key_size
        type: u4
        if: file_version.to_i >= replay_version_history::history_encryption.to_i
        doc: Size of encryption key in bytes
      - id: encryption_key
        size: encryption_key_size
        if: file_version.to_i >= replay_version_history::history_encryption.to_i
        doc: AES encryption key

  replay_chunk:
    doc: |
      A chunk in the replay file. The file consists of multiple chunks
      of different types containing headers, replay data, checkpoints, and events.
    seq:
      - id: chunk_type
        type: u4
        enum: replay_chunk_type
        doc: Type of this chunk
      - id: chunk_size
        type: s4
        doc: Size of chunk data in bytes
      - id: chunk_data
        size: chunk_size
        type:
          switch-on: chunk_type
          cases:
            'replay_chunk_type::header': header_chunk
            'replay_chunk_type::replay_data': replay_data_chunk
            'replay_chunk_type::checkpoint': checkpoint_chunk
            'replay_chunk_type::event': event_chunk
        doc: Chunk payload (may be encrypted/compressed)

  header_chunk:
    doc: |
      Network header chunk containing version information.
      See DemoNetDriver.h line 191
    seq:
      - id: magic
        contents: [0x3d, 0xa1, 0xf5, 0x2c]
        doc: Network magic number 0x2CF5A13D (little-endian)
      - id: network_version
        type: u4
        enum: network_version_history
        doc: Network version history
      - id: custom_versions
        type: custom_version_array
        if: network_version.to_i >= network_version_history::history_use_custom_version.to_i
        doc: Custom version information
      - id: network_checksum
        type: u4
        doc: Network checksum for compatibility
      - id: engine_network_version
        type: u4
        enum: engine_network_version_history
        doc: Engine network version
      - id: game_network_protocol_version
        type: u4
        doc: Game-specific network protocol version
      - id: guid
        size: 16
        if: network_version.to_i >= network_version_history::history_header_guid.to_i
        doc: Unique replay GUID (16 bytes)
      - id: version_full
        type: engine_version_full
        if: network_version.to_i >= network_version_history::history_save_full_engine_version.to_i
        doc: Full engine version info
      - id: changelist_legacy
        type: u4
        if: network_version.to_i < network_version_history::history_save_full_engine_version.to_i
        doc: Changelist (legacy format)
      - id: recording_metadata
        type: recording_metadata
        if: network_version.to_i >= network_version_history::history_recording_metadata.to_i
        doc: Recording metadata (UE4/UE5 version info)
      - id: level_names_and_times
        type: level_names_and_times_array
        doc: Array of level names with their times
      - id: flags
        type: u4
        if: network_version.to_i >= network_version_history::history_header_flags.to_i
        doc: Replay header flags (bitmask)
      - id: game_specific_data
        type: fstring_array
        doc: Game-specific data strings
      - id: package_version_info
        type: package_version_info
        if: network_version.to_i >= network_version_history::history_save_package_version_ue.to_i
        doc: Package version and platform info

  replay_data_chunk:
    doc: |
      Replay data chunk containing recorded network frames.
      Data may be compressed and/or encrypted based on replay_info flags.
    seq:
      - id: start_time
        type: u4
        if: _root.replay_info.file_version.to_i >= replay_version_history::history_stream_chunk_times.to_i
        doc: Start time in milliseconds
      - id: end_time
        type: u4
        if: _root.replay_info.file_version.to_i >= replay_version_history::history_stream_chunk_times.to_i
        doc: End time in milliseconds
      - id: data_length
        type: u4
        if: _root.replay_info.file_version.to_i >= replay_version_history::history_stream_chunk_times.to_i
        doc: Length of the following data
      - id: memory_size_in_bytes
        type: s4
        if: _root.replay_info.file_version.to_i >= replay_version_history::history_encryption.to_i
        doc: Memory size when decompressed
      - id: data
        size-eos: true
        doc: |
          Replay frame data. If compressed, starts with decompressed_size (u4),
          compressed_size (u4), then compressed bytes. Contains demo frames
          with network packets.

  checkpoint_chunk:
    doc: |
      Checkpoint chunk for fast-forwarding through replay.
      Contains actor state snapshots.
    seq:
      - id: id
        type: fstring
        doc: Checkpoint identifier
      - id: group
        type: fstring
        doc: Checkpoint group name
      - id: metadata
        type: fstring
        doc: Custom metadata
      - id: start_time
        type: u4
        doc: Start time in milliseconds
      - id: end_time
        type: u4
        doc: End time in milliseconds
      - id: size_in_bytes
        type: s4
        doc: Size of checkpoint data
      - id: data
        size: size_in_bytes
        doc: |
          Checkpoint data (may be encrypted/compressed).
          Contains: deleted startup actors, GUID cache, net field export groups,
          and serialized frame data.

  event_chunk:
    doc: |
      Custom event chunk for game-specific events (kills, stats, etc.)
    seq:
      - id: id
        type: fstring
        doc: Event identifier
      - id: group
        type: fstring
        doc: Event group name
      - id: metadata
        type: fstring
        doc: Custom metadata
      - id: start_time
        type: u4
        doc: Event start time in milliseconds
      - id: end_time
        type: u4
        doc: Event end time in milliseconds
      - id: size_in_bytes
        type: s4
        doc: Size of event data
      - id: data
        size: size_in_bytes
        doc: Event-specific binary data

  # ============================================================================
  # Helper Types
  # ============================================================================

  fstring:
    doc: |
      Unreal Engine FString serialization.
      Length is signed: positive = ASCII/UTF-8, negative = UTF-16 (abs(len) * 2 bytes)
    seq:
      - id: length
        type: s4
        doc: String length (negative for Unicode)
      - id: value_ascii
        type: str
        size: length
        encoding: UTF-8
        if: length > 0
        doc: ASCII/UTF-8 string data (including null terminator)
      - id: value_unicode
        type: str
        size: -length * 2
        encoding: UTF-16LE
        if: length < 0
        doc: Unicode string data (including null terminator)

  custom_version_array:
    doc: Array of custom versions (GUID + version number)
    seq:
      - id: count
        type: s4
        doc: Number of custom versions
      - id: entries
        type: custom_version_entry
        repeat: expr
        repeat-expr: count

  custom_version_entry:
    doc: A single custom version entry (20 bytes total)
    seq:
      - id: guid
        size: 16
        doc: Version GUID
      - id: version
        type: s4
        doc: Version number

  engine_version_full:
    doc: Full engine version information
    seq:
      - id: major
        type: u2
        doc: Major version number
      - id: minor
        type: u2
        doc: Minor version number
      - id: patch
        type: u2
        doc: Patch version number
      - id: changelist
        type: u4
        doc: Engine changelist
      - id: branch
        type: fstring
        doc: Branch name string

  recording_metadata:
    doc: Recording metadata for UE4/UE5 version info
    seq:
      - id: ue4_version
        type: u4
        doc: UE4 package file version
      - id: ue5_version
        type: u4
        doc: UE5 package file version
      - id: package_version_licensee_ue
        type: u4
        doc: Licensee UE package version

  level_names_and_times_array:
    doc: Array of level names with their associated times
    seq:
      - id: count
        type: u4
        doc: Number of levels
      - id: entries
        type: level_name_and_time
        repeat: expr
        repeat-expr: count

  level_name_and_time:
    doc: Level name with its time offset
    seq:
      - id: name
        type: fstring
        doc: Level name/path
      - id: time
        type: u4
        doc: Time offset in milliseconds

  fstring_array:
    doc: Array of FStrings
    seq:
      - id: count
        type: u4
        doc: Number of strings
      - id: entries
        type: fstring
        repeat: expr
        repeat-expr: count

  package_version_info:
    doc: Package version and platform information
    seq:
      - id: min_record_hz
        type: f4
        doc: Minimum recording rate in Hz
      - id: max_record_hz
        type: f4
        doc: Maximum recording rate in Hz
      - id: frame_limit_in_ms
        type: f4
        doc: Frame limit in milliseconds
      - id: checkpoint_limit_in_ms
        type: f4
        doc: Checkpoint limit in milliseconds
      - id: platform
        type: fstring
        doc: Platform name (e.g., "Windows")
      - id: build_config
        type: u1
        doc: Build configuration
      - id: build_target_type
        type: u1
        enum: build_target_type
        doc: Build target type

# ============================================================================
# Enumerations
# ============================================================================

enums:
  replay_version_history:
    0: history_initial
    1: history_fixedsize_friendly_name
    2: history_compression
    3: history_recorded_timestamp
    4: history_stream_chunk_times
    5: history_friendly_name_encoding
    6: history_encryption
    7: history_custom_versions

  replay_chunk_type:
    0: header
    1: replay_data
    2: checkpoint
    3: event
    0xffffffff: unknown

  network_version_history:
    1: history_replay_initial
    2: history_save_abs_time_ms
    3: history_increase_buffer
    4: history_save_engine_version
    5: history_extra_version
    6: history_multiple_levels
    7: history_multiple_levels_time_changes
    8: history_deleted_startup_actors
    9: history_header_flags
    10: history_level_streaming_fixes
    11: history_save_full_engine_version
    12: history_header_guid
    13: history_character_movement
    14: history_character_movement_nointerp
    15: history_guid_nametable
    16: history_guidcache_checksums
    17: history_save_package_version_ue
    18: history_recording_metadata
    19: history_use_custom_version

  engine_network_version_history:
    1: history_initial
    2: history_replay_backwards_compat
    3: history_max_actor_channels_customization
    4: history_repcmd_checksum_remove_printf
    5: history_new_actor_override_level
    6: history_channel_names
    7: history_channel_close_reason
    8: history_acks_included_in_header
    9: history_netexport_serialization
    10: history_netexport_serialize_fix
    11: history_fast_array_delta_struct
    12: history_fix_enum_serialization
    13: history_optionally_quantize_spawn_info
    14: history_jitter_in_header
    15: history_classnetcache_fullname
    16: history_replay_dormancy
    17: history_enum_serialization_compat
    18: history_subobject_outer_chain
    19: history_hitresult_instancehandle
    20: history_interface_property_serialization
    21: history_montage_play_inst_id_serialization
    22: history_serialize_double_vectors_as_doubles
    23: history_packed_vector_lwc_support
    24: history_pawn_remoteviewpitch
    25: history_repmove_serverframe_and_handle
    26: history_21_and_viewpitch_only_do_not_use
    27: history_placeholder
    28: history_runtime_features_compatibility
    29: history_softobjectptr_netguids
    30: history_subobject_destroy_flag
    31: history_gamestate_replicated_time_as_double
    32: history_customversion
    33: dynamic_montage_serialization
    34: prediction_key_base_not_replicated
    35: rep_move_optional_acceleration
    36: custom_exports

  replay_header_flags:
    0: none
    1: client_recorded
    2: has_streaming_fixes
    4: delta_checkpoints
    8: game_specific_frame_data
    16: replay_connection
    32: actor_prioritization_enabled
    64: net_relevancy_enabled
    128: async_recorded

  build_target_type:
    0: unknown
    1: game
    2: server
    3: client
    4: editor
    5: program
