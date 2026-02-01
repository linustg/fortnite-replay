#!/bin/bash

# Build script for Fortnite Replay Parser
# Supports: Linux (Ubuntu), macOS, Windows (Git Bash/MSYS2/WSL)

set -e  # Exit on error

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}Building Fortnite Replay Parser${NC}"

# Detect OS and set platform-specific variables
detect_platform() {
    case "$(uname -s)" in
        Linux*)
            OS="Linux"
            NPROC=$(nproc)
            ;;
        Darwin*)
            OS="macOS"
            NPROC=$(sysctl -n hw.ncpu)
            ;;
        CYGWIN*|MINGW*|MSYS*)
            OS="Windows"
            NPROC=${NUMBER_OF_PROCESSORS:-4}
            ;;
        *)
            OS="Unknown"
            NPROC=4
            ;;
    esac
    echo -e "${GREEN}Detected OS: ${OS}${NC}"
    echo -e "${GREEN}Using ${NPROC} parallel jobs${NC}"
}

# Detect C++ compiler (can be overridden via CXX environment variable)
detect_compiler() {
    if [ -n "$CXX" ]; then
        COMPILER="$CXX"
    elif command -v clang++ &> /dev/null; then
        COMPILER="clang++"
    elif command -v g++ &> /dev/null; then
        COMPILER="g++"
    elif command -v c++ &> /dev/null; then
        COMPILER="c++"
    else
        echo -e "${GREEN}No C++ compiler found, letting CMake decide${NC}"
        COMPILER=""
    fi

    if [ -n "$COMPILER" ]; then
        echo -e "${GREEN}Using C++ compiler: ${COMPILER}${NC}"
        CMAKE_CXX_FLAG="-DCMAKE_CXX_COMPILER=${COMPILER}"
    else
        CMAKE_CXX_FLAG=""
    fi
}

detect_platform
detect_compiler

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo -e "${GREEN}Configuring project...${NC}"
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    ${CMAKE_CXX_FLAG}

# Build
echo -e "${GREEN}Building...${NC}"
cmake --build . -j"${NPROC}"

# Run tests
echo -e "${GREEN}Running tests...${NC}"
ctest --output-on-failure

echo -e "${GREEN}Build complete!${NC}"