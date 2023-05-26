#ifndef __NK_ENVIRONMENT_CONFIGURATION__
#define __NK_ENVIRONMENT_CONFIGURATION__
#include <cstdlib>
#define NK_DEBUG_WITH_TYPE(X)                                                                      \
  do {                                                                                             \
    if (nk::EnvironmentConfiguration::getInstance().isDebug()) {                                   \
      X;                                                                                           \
    }                                                                                              \
  } while (false)

#define NK_TRACE(MSG) NK_DEBUG_WITH_TYPE(std::cout << (MSG));
namespace nk {

class EnvironmentConfiguration {
private:
  EnvironmentConfiguration() {
  }
  bool debug = false;

public:
  static EnvironmentConfiguration &getInstance() {
    static EnvironmentConfiguration instance;
    return instance;
  }
  void init() {
    if (getenv("NK_COMPILE_DEBUG") != nullptr) {
      debug = true;
    }
  }
  const bool isDebug() {
    return debug;
  }
};
} // namespace nk

#endif