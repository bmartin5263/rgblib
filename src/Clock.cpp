//
// Created by Brandon on 1/5/25.
//

#include "Clock.h"
#include "Arduino.h"
#include "Log.h"

auto Clock::Instance() -> Clock& {
  static Clock instance;
  return instance;
}

auto Clock::init(ft targetFps) -> void {
  this->targetFps = targetFps;
}

auto Clock::startTick() -> void {
  ms currentTime = milli();
  ms elapsed = currentTime - lastTime;

  if (elapsed >= 1000) { // Update every second
    Log::Info("FPS: ");
    Log::InfoLn(fpsCounter);

    fpsCounter = 0;
    lastTime = currentTime;
  }

  ++fpsCounter;
  ++frameTime;
}

auto Clock::frames() const -> ft {
  return frameTime;
}

auto Clock::milli() const -> ms {
  return millis();
}

auto Clock::time() const -> ClockTime {
  return {milli(), frameTime};
}

auto Clock::stopTick() const -> void {
  ms MAX_MS = 5;
  auto stop = milli();
  auto time = stop - tickStart;
  i64 m = MAX_MS - time;
  auto sleep = _max(m, 0u);
  delay(sleep);
}

auto Clock::Init(ft fps) -> void {
  Instance().init(fps);
}

auto Clock::StartTick() -> void {
  Instance().startTick();
}

auto Clock::Frames() -> ft {
  return Instance().frames();
}

auto Clock::Milli() -> ms {
  return Instance().milli();
}

auto Clock::Time() -> ClockTime {
  return Instance().time();
}

auto Clock::StopTick() -> void {
  Instance().stopTick();
}