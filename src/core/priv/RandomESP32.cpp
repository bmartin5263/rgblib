//
// Created by Brandon on 8/10/26.
//

#if defined(RGB_ARDUINO_ESP32) || defined(RGB_ESP32)

#include "RandomESP32.h"
#include <esp_random.h>

namespace rgb::priv {

auto RandomESP32::next() -> u32 {
  return esp_random();
}

}

#endif //defined(RGB_ARDUINO_ESP32) || defined(RGB_ESP32)
