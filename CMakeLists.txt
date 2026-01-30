cmake_minimum_required(VERSION 3.20)
project(UnrealCryptoLib VERSION 1.0.0 LANGUAGES CXX)

# Use C++23 (or C++20 if you prefer)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Find required packages
find_package(GTest REQUIRED)

# Fetch Kaitai Struct C++ runtime (using master for C++23 compatibility)
include(FetchContent)
FetchContent_Declare(
    kaitai_struct_cpp_stl_runtime
    GIT_REPOSITORY https://github.com/kaitai-io/kaitai_struct_cpp_stl_runtime.git
    GIT_TAG        master
)
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