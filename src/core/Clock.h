//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_CLOCK_H
#define RGBLIB_CLOCK_H

#include "Types.h"
#include "System.h"
#include "ClockImpl.h"

namespace rgb {

class Clock {
public:
  static auto NextFrame() -> void { Implementation().nextFrame(); }
  static auto Start() -> void { Implementation().start(); }
  static auto Now() -> Timestamp { return Timestamp{System::MicroTime()}; }
  static auto Delta() -> Duration { return Duration{ Implementation().delta() }; }
  static auto Fps() -> uint { return Implementation().fps(); }

private:
  static auto Implementation() -> priv::ClockImpl&;
  priv::ClockImpl impl;
};

inline auto Clock::Implementation() -> priv::ClockImpl& {
  static Clock instance;
  return instance.impl;
}

}


#endif //RGBLIB_CLOCK_H
