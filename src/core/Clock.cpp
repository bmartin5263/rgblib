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

auto Clock::initialize(u16 targetFps) -> void {
  this->targetFps = targetFps;
}

auto Clock::startTick() -> void {
  u32 currentTime = millis();
  u32 elapsed = currentTime - lastTimeMs;

  if (elapsed >= 1000) { // Update every second
    Log::Info("FPS: ");
    Log::InfoLn(globalFpsCounter);

    globalFpsCounter = 0;
    lastTimeMs = currentTime;
  }

  ++globalFpsCounter;
  ++_globalFrame;
}

auto Clock::frames() -> u32 {
  return _globalFrame;
}

auto Clock::milli() -> u32 {
  return millis();
}

auto Clock::time() -> ClockTime {
  return {millis(), _globalFrame};
}

auto Clock::stopTick() -> void {
  auto MAX_MS = 5;
  auto stop = millis();
  auto time = stop - tickStart;
  i32 m = MAX_MS - time;
  auto sleep = _max(m, 0u);
  delay(sleep);
}