//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_CLOCKBASE_H
#define RGBLIB_CLOCKBASE_H

#include "Types.h"
#include "System.h"

namespace rgb::priv {

class ClockBase {
public:
  auto delta() const -> microseconds_t { return mDelta; }
  auto fps() const -> uint { return mLastFps; }

protected:
  auto resetTiming() -> void {
    mFrameStartTime = System::MicroTime();
    mLastFrameRateCheck = mFrameStartTime;
  }

  auto recordFrame() -> void {
    auto now = System::MicroTime();
    mDelta = now - mFrameStartTime;
    mFrameStartTime = now;

    auto elapsed = mFrameStartTime - mLastFrameRateCheck;
    if (elapsed >= 1'000'000) { // Update every second
      mLowFpsDetected = mFpsCounter < 100;
      mLastFps = mFpsCounter;
      mFpsCounter = 0;
      mLastFrameRateCheck = mFrameStartTime;
    }

    ++mFpsCounter;
    ++mFrames;
  }

private:
  frames_t mFrames{};
  frames_t mFpsCounter{};
  frames_t mLastFps{};
  u64 mNextFrame{};
  microseconds_t mFrameStartTime{};
  microseconds_t mLastFrameRateCheck{};
  microseconds_t mDelta{};
  bool mLowFpsDetected{};
};

}

#endif //RGBLIB_CLOCKBASE_H
