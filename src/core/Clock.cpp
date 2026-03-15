//
// Created by Brandon on 1/5/25.
//

#include "Clock.h"
#include "Log.h"
#include "System.h"

namespace rgb {

auto Clock::nextFrame() -> void {
  vTaskDelayUntil(&lastWakeTime, frequency);

  mTickStart = System::MilliTime();
  auto elapsed = mTickStart - mLastFrameRateCheck;

  if (elapsed >= 1000) { // Update every second
    if (mFpsCounter < (mTargetFps / 2)) {
      if (!lowFpsDetected) {
        lowFpsDetected = true;
        // Do callback
      }
    }
    else {
      if (lowFpsDetected) {
        lowFpsDetected = false;
        // Do recover callback
      }
    }

    mLastFps = mFpsCounter;
    mFpsCounter = 0;
    mLastFrameRateCheck = mTickStart;
  }
  ++mFpsCounter;
  ++mFrames;
}

auto Clock::Instance() -> Clock& {
  static Clock instance;
  return instance;
}

auto Clock::start(frames_t fps) -> void {
  mTargetFps = fps;
  mMaxMillisecondsPerFrame = 1000 / fps;
}

auto Clock::fps() const -> uint {
  return mLastFps;
}

}