# Test executable
add_executable(fortnite_replay_tests
    test_parser.cpp
    test_replay.cpp
    test_crypto.cpp
)

# Link with library and Google Test
target_link_libraries(fortnite_replay_tests
    PRIVATE
        fortnite_replay
        GTest::gtest
        GTest::gtest_main
)

# Set RPATH for finding shared libraries at runtime
set_target_properties(fortnite_replay_tests PROPERTIES
    BUILD_RPATH_USE_ORIGIN ON
    BUILD_RPATH "$<TARGET_FILE_DIR:fortnite_replay>;$<TARGET_FILE_DIR:GTest::gtest>"
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(fortnite_replay_tests
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    DISCOVERY_MODE PRE_TEST
    PROPERTIES
        ENVIRONMENT "GTEST_COLOR=1"
)