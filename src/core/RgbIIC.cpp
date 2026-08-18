//
// Created by Brandon on 8/10/26.
//

#include "RgbIIC.h"

#if defined(RGB_ARDUINO_ESP32)

namespace rgb {

auto IIC::Implementation() -> priv::IICImpl& {
  static IIC instance;
  return instance.impl;
}

auto IIC::Start() -> bool {
  return Implementation().start();
}

auto IIC::Stop() -> void {
  Implementation().stop();
}

auto IIC::IsStarted() -> bool {
  return Implementation().isStarted();
}

}

#endif //defined(RGB_ARDUINO_ESP32)
