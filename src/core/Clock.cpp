//
// Created by Brandon on 1/5/25.
//

#include "Clock.h"
#include "Log.h"
#include "System.h"

namespace rgb {

auto Clock::nextFrame() -> void {
  xTaskDelayUntil(&lastWakeTime, frequency);
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

auto Clock::Instance() -> Clock& {
  static Clock instance;
  return instance;
}

auto Clock::start() -> void {
  lastWakeTime = xTaskGetTickCount();
  mFrameStartTime = System::MicroTime();
}

auto Clock::fps() const -> uint {
  return mLastFps;
}

}