//
// Created by Brandon on 5/6/26.
//

#ifndef RGBLIB_RTCIMPLEMENTATION_H
#define RGBLIB_RTCIMPLEMENTATION_H

#include <RgbIIC.h>
#include <RTClib.h>

namespace rgb::priv {
class RTCImpl {
public:
  auto start(TwoWire* wire = &Wire) -> bool;
  auto adjust(const DateTime& dt) -> void;
  auto now() -> DateTime;

private:
  RTC_DS3231 mRtc{};
  bool mStarted{};
};

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
  mRtc.adjust(dt);
}

auto RTCImpl::now() -> DateTime {
  return mRtc.now();
}

};

#endif //RGBLIB_RTCIMPLEMENTATION_H
