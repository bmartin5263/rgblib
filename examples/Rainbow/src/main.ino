#if RGB_ARDUINO_ESP32

#include "RainbowApplication.h"

auto app = RainbowApplication{};

auto setup() -> void {
  app.setup();
}

auto loop() -> void {
  app.loop();
}

#endif //defined(RGB_ARDUINO_ESP32)
