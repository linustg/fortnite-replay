# Test executable
add_executable(fortnite_replay_tests
    test_parser.cpp
    test_replay.cpp
)

# Link with library and Google Test
target_link_libraries(fortnite_replay_tests
    PRIVATE
        fortnite_replay
        GTest::gtest
        GTest::gtest_main
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(fortnite_replay_tests
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    PROPERTIES
        ENVIRONMENT "GTEST_COLOR=1"
)