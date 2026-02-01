# Library source files
set(LIB_SOURCES
    crypto.cpp
    event_parser.cpp
    parser.cpp
    replay.cpp
    ${CMAKE_SOURCE_DIR}/generated/fortnite_replay.cpp
)

# Create shared library
add_library(fortnite_replay SHARED ${LIB_SOURCES})

# Link against kaitai struct runtime and crypto libraries
target_link_libraries(fortnite_replay
    PUBLIC
        kaitai_struct_cpp_stl_runtime
    PRIVATE
        OpenSSL::Crypto
        ZLIB::ZLIB
        ${CMAKE_DL_LIBS}  # For dlopen/dlsym on Unix
)

# Include directories
target_include_directories(fortnite_replay
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/generated
)

# Install library
install(TARGETS fortnite_replay
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)