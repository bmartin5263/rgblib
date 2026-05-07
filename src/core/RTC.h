//
// Created by Brandon on 5/6/26.
//

#ifndef RGBLIB_RTC_H
#define RGBLIB_RTC_H

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

auto RTC::Implementation() -> priv::RTCImpl& {
  static RTC instance;
  return instance.impl;
}

auto RTC::Start(TwoWire* wire) -> bool {
  return Implementation().start(wire);
}

auto RTC::Adjust(const DateTime& dt) -> void {
  Implementation().adjust(dt);
}

auto RTC::Now() -> DateTime {
  return Implementation().now();
}

}

#endif //RGBLIB_RTC_H
