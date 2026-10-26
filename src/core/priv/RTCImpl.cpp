//
// Created by Brandon on 8/10/26.
//

#if RGB_ARDUINO_ESP32

#include "RTCImpl.h"

namespace rgb::priv {

auto RTCImpl::start(TwoWire* wire) -> bool {
  if (!IIC::Start()) {
    ERROR("RTC failed to start - IIC start failed");
    return false;
  }
  mStarted = mRtc.begin(wire);
  if (!mStarted) {
    ERROR("RTC failed to start - RTC start failed");
  }
  return mStarted;
}

auto RTCImpl::adjust(const DateTime& dt) -> void {
  if (!mStarted) {
    ERROR("Cannot adjust - RTC not started");
  }
  mRtc.adjust(dt);
}

auto RTCImpl::adjustToCompileTime() -> void {
  if (!mStarted) {
    ERROR("Cannot adjust - RTC not started");
  }
  mRtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

auto RTCImpl::now() -> DateTime {
  if (!mStarted) {
    ERROR("Cannot get current time - RTC not started");
    return DateTime{};
  }
  return mRtc.now();
}

}

#endif //defined(RGB_ARDUINO_ESP32)
