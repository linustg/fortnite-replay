# Project Setup and Documentation Guide

This document provides an overview of the project's documentation and CI/CD setup.

## Documentation Files

### Main Documentation

- **[README.md](../README.md)** - Main project README with:
  - Project badges (CI, License, Codecov, C++ Standard, Platform)
  - Features overview
  - Quick start guide
  - Usage examples
  - API reference summary
  - Building instructions
  - Contributing guidelines

- **[CONTRIBUTING.md](../CONTRIBUTING.md)** - Contributor guidelines including:
  - Development setup
  - Workflow and branching strategy
  - Code style guidelines
  - Testing requirements
  - PR process
  - Code of conduct

- **[LICENSE](../LICENSE)** - MIT License

### API Documentation

- **[docs/API.md](API.md)** - Comprehensive API documentation:
  - Parser API (`FortniteReplayParser`)
  - Replay Model API (`Replay`, `ReplayInfo`)
  - Chunk Types (`HeaderChunk`, `DataChunk`, `CheckpointChunk`, `EventChunk`)
  - Data Structures (`EngineVersion`, `ReplayHeaderFlags`, etc.)
  - Usage examples and best practices

### Example Documentation

- **[examples/README.md](../examples/README.md)** - Example program documentation:
  - Usage instructions for replay viewer
  - Feature demonstrations
  - Code structure explanation
  - Integration examples

## CI/CD Setup

### GitHub Actions Workflow

**File:** `.github/workflows/ci.yml`

#### Jobs

1. **build-and-test**
   - Runs on: Linux, macOS, Windows
   - Build types: Debug, Release
   - Compilers: GCC (Linux), Clang (macOS), MSVC (Windows)
   - Steps:
     - Checkout code
     - Install dependencies
     - Configure with CMake
     - Build project
     - Run tests
     - Build example

2. **code-coverage**
   - Runs on: Ubuntu (latest)
   - Generates code coverage with lcov
   - Uploads to Codecov
   - Requires `CODECOV_TOKEN` secret

3. **static-analysis**
   - Runs on: Ubuntu (latest)
   - Tools: cppcheck
   - Analyzes code quality

4. **formatting-check**
   - Runs on: Ubuntu (latest)
   - Tool: clang-format
   - Checks code formatting

#### Triggers

- Push to `main` branch
- Pull requests to `main` branch

### GitHub Templates

- **[.github/PULL_REQUEST_TEMPLATE.md](../.github/PULL_REQUEST_TEMPLATE.md)**
  - PR description template
  - Change type checklist
  - Testing checklist
  - Review checklist

- **[.github/ISSUE_TEMPLATE/bug_report.md](../.github/ISSUE_TEMPLATE/bug_report.md)**
  - Bug report template
  - Reproduction steps
  - Environment information

- **[.github/ISSUE_TEMPLATE/feature_request.md](../.github/ISSUE_TEMPLATE/feature_request.md)**
  - Feature request template
  - Use case description
  - Proposed API example

## Badges

The README includes the following badges:

### CI Status
```markdown
[![CI](https://github.com/linustg/fortnite-replay/actions/workflows/ci.yml/badge.svg)](https://github.com/linustg/fortnite-replay/actions/workflows/ci.yml)
```
Shows the status of the CI workflow (passing/failing).

### License
```markdown
[![License](https://img.shields.io/github/license/linustg/fortnite-replay)](LICENSE)
```
Displays the project license (MIT).

### Code Coverage
```markdown
[![codecov](https://codecov.io/gh/linustg/fortnite-replay/branch/main/graph/badge.svg)](https://codecov.io/gh/linustg/fortnite-replay)
```
Shows code coverage percentage from Codecov.

### C++ Standard
```markdown
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
```
Indicates C++23 requirement.

### Platform Support
```markdown
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey)](https://github.com/linustg/fortnite-replay)
```
Shows supported platforms.

## Required GitHub Secrets

To enable all CI features, configure these secrets in your GitHub repository settings:

1. **CODECOV_TOKEN**
   - Required for code coverage upload
   - Get from: https://codecov.io/
   - Settings → Secrets and variables → Actions → New repository secret

### Setting up Codecov

1. Go to https://codecov.io/
2. Sign in with GitHub
3. Add the repository
4. Copy the upload token
5. Add as `CODECOV_TOKEN` secret in GitHub

## Local Development Setup

### Prerequisites

- C++23 compatible compiler (GCC 11+, Clang 14+, MSVC 2022+)
- CMake 3.20+
- Git
- Google Test (auto-fetched)

### Build and Test

```bash
# Clone repository
git clone https://github.com/linustg/fortnite-replay.git
cd fortnite-replay

# Build
./build.sh

# Run tests
cd build
ctest --output-on-failure

# Build documentation
# (Add Doxygen setup if needed)
```

## Project Structure

```
fortnite-replay/
├── .github/
│   ├── workflows/
│   │   └── ci.yml                 # GitHub Actions workflow
│   ├── ISSUE_TEMPLATE/
│   │   ├── bug_report.md          # Bug report template
│   │   └── feature_request.md     # Feature request template
│   └── PULL_REQUEST_TEMPLATE.md   # PR template
├── docs/
│   ├── API.md                     # API documentation
│   └── SETUP.md                   # This file
├── examples/
│   ├── example_main.cpp           # Replay viewer example
│   ├── CMakeLists.txt
│   └── README.md                  # Example documentation
├── include/fortnite_replay/       # Public headers
├── src/                           # Implementation
├── tests/                         # Unit tests
├── README.md                      # Main README
├── CONTRIBUTING.md                # Contribution guide
├── LICENSE                        # MIT License
├── CMakeLists.txt                 # Root CMake config
└── build.sh                       # Build script
```

## Next Steps

1. **Enable GitHub Actions**
   - Push code to GitHub
   - Workflows will run automatically

2. **Set up Codecov**
   - Add `CODECOV_TOKEN` secret
   - Coverage reports will be generated

3. **Create First Release**
   - Tag a version: `git tag v1.0.0`
   - Push tag: `git push origin v1.0.0`
   - GitHub will create a release

4. **Add Documentation Badge** (optional)
   - Set up GitHub Pages
   - Generate API docs with Doxygen
   - Add docs badge to README

## Continuous Improvement

### Recommended Additions

- [ ] Doxygen configuration for API docs
- [ ] GitHub Pages for documentation hosting
- [ ] Release workflow for automatic releases
- [ ] Dependency scanning (Dependabot)
- [ ] Security scanning (CodeQL)
- [ ] Performance benchmarks
- [ ] Docker container for reproducible builds

### Monitoring

- Check GitHub Actions tab for workflow runs
- Monitor Codecov dashboard for coverage trends
- Review pull requests with automated checks
- Track issues and feature requests

## Support

For questions about setup:
- Open an issue with the "question" label
- Check existing documentation
- Review GitHub Discussions

---

Last updated: 2024
