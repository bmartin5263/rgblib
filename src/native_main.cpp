//
// Created by Brandon on 8/17/26.
//

#if RGB_NATIVE

#include "app/SandboxApplication.h"
auto app = SandboxApplication{};

auto main() -> int {
  app.run();
  return 0;
}

#endif //defined(RGB_NATIVE)
