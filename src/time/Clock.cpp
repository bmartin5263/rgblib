//
// Created by Brandon on 1/5/25.
//

#include "time/Clock.h"
#include "Arduino.h"
#include "Log.h"

namespace rgb {

auto Clock::Instance() -> Clock& {
  static Clock instance;
  return instance;
}

auto Clock::init(frames_t targetFps) -> void {
  this->mTargetFps = targetFps;
  this->mMaxMicrosPerFrame = 1000000 / targetFps;
}

auto Clock::startTick() -> void {
  mTickStart = micros();
  auto elapsed = mTickStart - mLastFrameRateCheck;

  if (elapsed >= 1'000'000) { // Update every second
    INFO("FPS: %lu", mFpsCounter);

    if (mFpsCounter < (mTargetFps / 2)) {
      digitalWrite(LED_RED, LOW);
    }
    else {
      digitalWrite(LED_RED, HIGH);
    }

    mLastFps = mFpsCounter;
    mFpsCounter = 0;
    mLastFrameRateCheck = mTickStart;

  }

  ++mFpsCounter;
  ++mFrames;
}

auto Clock::frames() const -> frames_t {
  return mFrames;
}

auto Clock::milli() const -> milliseconds_t {
  return millis();
}

auto Clock::stopTick() -> void {
  auto stop = micros();
  auto duration = stop - mTickStart;
  if (duration >= mMaxMicrosPerFrame) {
    return;
  }

  auto sleep = mMaxMicrosPerFrame - duration;
  mDelta = duration + sleep;
  delayMicroseconds(sleep);
}

auto Clock::Init(frames_t fps) -> void {
  Instance().init(fps);
}

auto Clock::StartTick() -> void {
  Instance().startTick();
}

auto Clock::Frames() -> frames_t {
  return Instance().frames();
}

auto Clock::Milli() -> milliseconds_t {
  return Instance().milli();
}

auto Clock::Now() -> Timestamp {
  return Timestamp::OfMicroseconds(micros());
}

auto Clock::Delta() -> Duration {
  return Instance().delta();
}

auto Clock::Fps() -> frames_t {
  return Instance().fps();
}

auto Clock::StopTick() -> void {
  Instance().stopTick();
}

auto Clock::delta() const -> Duration {
  return Duration { mDelta };
}

auto Clock::fps() const -> frames_t {
  return mLastFps;
}

}