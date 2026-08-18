//
// Created by Brandon on 8/10/26.
//

#if defined(RGB_ARDUINO_ESP32)

#include "IICArduino.h"

namespace rgb::priv {

auto IICArduino::start() -> bool {
  if (!mStarted) {
    mStarted = Wire.begin(RGB_IIC_SDA, RGB_IIC_SCL);
  }
  return mStarted;
}

auto IICArduino::stop() -> void {
  if (mStarted) {
    Wire.end();
    mStarted = false;
  }
}

auto IICArduino::isStarted() const -> bool {
  return mStarted;
}

}

#endif //defined(RGB_ARDUINO_ESP32)
