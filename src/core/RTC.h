//
// Created by Brandon on 5/6/26.
//

#ifndef RGBLIB_RTC_H
#define RGBLIB_RTC_H

#if RGB_ARDUINO_ESP32

#include "RTCImpl.h"

namespace rgb {

class RTC {
public:
  static auto Start(TwoWire* wire = &Wire) -> bool;
  static auto Adjust(const DateTime& dt) -> void;
  static auto Now() -> DateTime;

private:
  static auto Implementation() -> priv::RTCImpl&;
  priv::RTCImpl impl;
};

}

#endif //defined(RGB_ARDUINO_ESP32)

#endif //RGBLIB_RTC_H
