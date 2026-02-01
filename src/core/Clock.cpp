//
// Created by Brandon on 1/5/25.
//

#include "Clock.h"
#include "Log.h"
#include "System.h"

namespace rgb {

auto Clock::Now() -> Timestamp {
  return Timestamp{System::MicroTime()};
}

auto Clock::printStats() -> void {
  auto elapsed = mTickStart - mLastFrameRateCheck;
  if (elapsed > 1000) {
//    INFO("FPS: %llu", mLastFps);
  }
}

auto Clock::startFrame() -> void {
  vTaskDelayUntil(&lastWakeTime, frequency);

  mTickStart = System::MilliTime();
  auto elapsed = mTickStart - mLastFrameRateCheck;

  if (elapsed >= 1000) { // Update every second
    INFO("FPS: %llu", mFpsCounter);

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

auto Clock::endFrame() -> void {

}

}