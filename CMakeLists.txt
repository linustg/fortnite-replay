cmake_minimum_required(VERSION 3.25)
project(UnrealCryptoLib VERSION 1.0.0 LANGUAGES CXX)

# Use C++23 (or C++20 if you prefer)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# RPATH settings for finding shared libraries at runtime
set(CMAKE_SKIP_BUILD_RPATH OFF)
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
    # Use @loader_path for finding libraries relative to the executable
    set(CMAKE_BUILD_RPATH "@loader_path/../src;@loader_path")
    set(CMAKE_INSTALL_RPATH "@loader_path/../lib")
elseif(UNIX)
    # Linux: use $ORIGIN for relative RPATH
    set(CMAKE_BUILD_RPATH "$ORIGIN/../src;$ORIGIN")
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()

# On Windows, put all DLLs and executables in the same directory
if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# Enable testing
enable_testing()

# Find required packages
find_package(GTest REQUIRED)

# Fetch Kaitai Struct C++ runtime (using master for C++23 compatibility)
include(FetchContent)

# Windows compatibility: create endian.h and byteswap.h wrappers
if(WIN32)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/compat)
    # Configure endian.h
    configure_file(
        ${CMAKE_SOURCE_DIR}/cmake/windows_compat.h
        ${CMAKE_BINARY_DIR}/compat/endian.h
        COPYONLY
    )
    # Configure byteswap.h
    configure_file(
        ${CMAKE_SOURCE_DIR}/cmake/byteswap.h
        ${CMAKE_BINARY_DIR}/compat/byteswap.h
        COPYONLY
    )
    include_directories(BEFORE SYSTEM ${CMAKE_BINARY_DIR}/compat)
endif()

FetchContent_Declare(
    kaitai_struct_cpp_stl_runtime
    GIT_REPOSITORY https://github.com/kaitai-io/kaitai_struct_cpp_stl_runtime.git
    GIT_TAG        master
)

# Disable tests for kaitai dependency
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(kaitai_struct_cpp_stl_runtime)

# Add compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)

# Installation rules
install(DIRECTORY include/ DESTINATION include)