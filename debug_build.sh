#!/bin/bash

# Debug Build script for Fortnite Replay Parser

set -e  # Exit on error

# Colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}Building Fortnite Replay Parser (Debug)${NC}"

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo -e "${GREEN}Configuring project...${NC}"
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_COMPILER=g++-13 \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build
echo -e "${GREEN}Building...${NC}"
cmake --build . -j$(nproc)

# Run tests
echo -e "${GREEN}Running tests...${NC}"
ctest --output-on-failure

echo -e "${GREEN}Debug build complete!${NC}"
