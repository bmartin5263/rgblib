//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_CLOCKNATIVE_H
#define RGBLIB_CLOCKNATIVE_H

#include "ClockBase.h"
#include "Types.h"
#include "System.h"

namespace rgb::priv {

class ClockNative : public ClockBase {
public:
  auto start() -> void {
    mNextFrameDeadline = System::MicroTime() + FRAME_PERIOD;
    resetTiming();
  }

  auto nextFrame() -> void {
    auto now = System::MicroTime();
    if (mNextFrameDeadline > now) {
      System::MicroSleep(mNextFrameDeadline - now);
    }
    mNextFrameDeadline += FRAME_PERIOD;
    recordFrame();
  }

private:
  static constexpr microseconds_t FRAME_PERIOD = 4'000; // ~250 FPS
  microseconds_t mNextFrameDeadline{};
};

}

#endif //RGBLIB_CLOCKNATIVE_H
