# Contributing to Fortnite Replay Parser

Thank you for your interest in contributing to the Fortnite Replay Parser project! We welcome contributions from the community.

## Getting Started

### Prerequisites

Before you begin, ensure you have:
- A C++23 compatible compiler (GCC 11+, Clang 14+, or MSVC 2022+)
- CMake 3.20 or higher
- Git
- Google Test (automatically fetched by CMake)

### Setting Up Your Development Environment

1. **Fork the repository**

   Click the "Fork" button at the top right of the repository page.

2. **Clone your fork**

   ```bash
   git clone https://github.com/YOUR_USERNAME/fortnite-replay.git
   cd fortnite-replay
   ```

3. **Add the upstream remote**

   ```bash
   git remote add upstream https://github.com/linustg/fortnite-replay.git
   ```

4. **Build the project**

   ```bash
   ./build.sh
   ```

## Development Workflow

### Creating a Branch

Always create a new branch for your work:

```bash
git checkout -b feature/your-feature-name
```

Use descriptive branch names:
- `feature/add-xyz` for new features
- `fix/issue-123` for bug fixes
- `docs/improve-readme` for documentation
- `refactor/cleanup-parser` for refactoring

### Making Changes

1. **Write your code**
   - Follow the existing code style and conventions
   - Use modern C++23 features appropriately
   - Keep functions focused and modular
   - Add comments for complex logic

2. **Write tests**
   - Add unit tests for new functionality
   - Ensure existing tests still pass
   - Aim for high test coverage

3. **Test your changes**

   ```bash
   ./build.sh
   cd build
   ctest --output-on-failure
   ```

4. **Update documentation**
   - Update README.md if you add new features
   - Add inline documentation for public APIs
   - Update example code if necessary

### Code Style Guidelines

- **Naming Conventions**
  - Classes: `PascalCase` (e.g., `FortniteReplayParser`)
  - Functions/methods: `snake_case` (e.g., `parse_replay()`)
  - Variables: `snake_case` (e.g., `chunk_count`)
  - Constants: `UPPER_SNAKE_CASE` (e.g., `MAX_CHUNK_SIZE`)
  - Private members: `m_` prefix (e.g., `m_chunks`)

- **Formatting**
  - Use 4 spaces for indentation (no tabs)
  - Keep lines under 100 characters where reasonable
  - Place opening braces on the same line for functions/classes
  - Use `nullptr` instead of `NULL`
  - Prefer `auto` when the type is obvious from context

- **Modern C++ Features**
  - Use `std::optional` for optional values
  - Use `std::unique_ptr`/`std::shared_ptr` for ownership
  - Use range-based for loops where appropriate
  - Prefer `constexpr` for compile-time constants
  - Use structured bindings when helpful

### Example Code Style

```cpp
class ExampleClass
{
public:
    ExampleClass() = default;

    // Public method with clear documentation
    bool parse_data(const std::string& filepath)
    {
        if (filepath.empty())
        {
            return false;
        }

        // Implementation here
        return true;
    }

    // Accessor methods
    size_t count() const { return m_count; }

private:
    size_t m_count = 0;
    std::vector<int> m_data;
};
```

### Committing Changes

1. **Stage your changes**

   ```bash
   git add <files>
   ```

2. **Commit with a descriptive message**

   ```bash
   git commit -m "Add feature: description of what you did"
   ```

   Good commit messages:
   - Start with a verb in present tense (Add, Fix, Update, Refactor)
   - Be specific and descriptive
   - Reference issue numbers when applicable (e.g., "Fix #123: ...")

   Examples:
   - ✅ "Add support for encrypted replay files"
   - ✅ "Fix memory leak in parser destructor"
   - ✅ "Update documentation for Replay class"
   - ❌ "Update"
   - ❌ "Fixed stuff"

3. **Push to your fork**

   ```bash
   git push origin feature/your-feature-name
   ```

### Creating a Pull Request

1. **Go to the repository on GitHub**

   Navigate to https://github.com/linustg/fortnite-replay

2. **Click "New Pull Request"**

3. **Select your branch**

   Choose your branch from your fork to compare against the main branch.

4. **Fill in the PR template**

   - Provide a clear title
   - Describe what your changes do
   - Reference any related issues
   - List any breaking changes
   - Add screenshots if applicable

5. **Submit the PR**

### PR Review Process

- A maintainer will review your PR
- You may be asked to make changes
- Address review comments and push updates
- Once approved, your PR will be merged

## Testing

### Running Tests

```bash
# Run all tests
cd build
ctest --output-on-failure

# Run specific test suite
./fortnite_replay_tests --gtest_filter=ReplayTest.*

# Run with verbose output
ctest -V
```

### Writing Tests

Tests use Google Test framework. Add tests in the `tests/` directory:

```cpp
#include <gtest/gtest.h>
#include "fortnite_replay/replay.hpp"

TEST(ReplayTest, YourTestName)
{
    // Arrange
    Replay replay;

    // Act
    replay.info().friendly_name = "Test";

    // Assert
    EXPECT_EQ(replay.friendly_name(), "Test");
}
```

## Reporting Issues

### Bug Reports

When reporting a bug, please include:

- A clear, descriptive title
- Steps to reproduce the issue
- Expected behavior
- Actual behavior
- System information (OS, compiler version, CMake version)
- Relevant code snippets or error messages
- Sample replay file if applicable (and if it doesn't contain sensitive data)

### Feature Requests

When suggesting a feature:

- Describe the feature clearly
- Explain the use case and why it would be valuable
- Provide examples of how it would work
- Consider backward compatibility

## Communication

- **Issues**: For bug reports and feature requests
- **Pull Requests**: For code contributions
- **Discussions**: For questions and general discussion

## Code of Conduct

### Our Standards

- Be respectful and inclusive
- Welcome newcomers and help them learn
- Focus on constructive criticism
- Accept feedback gracefully
- Prioritize the health of the community

### Unacceptable Behavior

- Harassment or discriminatory language
- Trolling or insulting comments
- Publishing others' private information
- Other conduct that would be inappropriate in a professional setting

## Questions?

If you have questions about contributing, feel free to:
- Open an issue with the "question" label
- Start a discussion on GitHub Discussions
- Reach out to the maintainers

## Attribution

By contributing to this project, you agree that your contributions will be licensed under the MIT License.

Thank you for contributing! 🎉
