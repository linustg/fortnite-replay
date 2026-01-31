# Example executable
add_executable(replay_viewer example_main.cpp)

# Link against the fortnite_replay library
target_link_libraries(replay_viewer PRIVATE fortnite_replay)

# Set output directory
set_target_properties(replay_viewer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
