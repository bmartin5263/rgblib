//
// Created by Brandon on 7/17/26.
//

#include "RTC.h"

namespace rgb {

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
