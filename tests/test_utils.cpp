#include <cstdlib>
#include <string>

namespace test_utils {

// Helper function to check if we're running in CI environment
inline bool is_ci_environment() {
  const char *ci_env = std::getenv("CI");
  const char *skip_oodle = std::getenv("SKIP_OODLE_TESTS");
  return (ci_env != nullptr && std::string(ci_env) == "true") ||
         (skip_oodle != nullptr && std::string(skip_oodle) == "true");
}

} // namespace test_utils