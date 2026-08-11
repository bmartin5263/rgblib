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

};

#endif //RGBLIB_RTCIMPLEMENTATION_H
