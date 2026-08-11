//
// Created by Brandon on 8/10/26.
//

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
  mRtc.adjust(dt);
}

auto RTCImpl::now() -> DateTime {
  return mRtc.now();
}

}