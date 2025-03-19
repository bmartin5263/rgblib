//
// Created by Brandon on 1/5/25.
//

#include "Clock.h"
#include "Arduino.h"
#include "Log.h"

namespace rgb {

auto Clock::Instance() -> Clock& {
  static Clock instance;
  return instance;
}

auto Clock::init(frames targetFps) -> void {
  this->maxMsPerFrame = 1000 / targetFps;
}

auto Clock::startTick() -> void {
  tickStart = milli();
  auto elapsed = tickStart - lastTime;

  if (elapsed >= 1000) { // Update every second
    Log.info("FPS: ").infoLn(fpsCounter);

    fpsCounter = 0;
    lastTime = tickStart;
  }

  ++fpsCounter;
  ++frameTimer;
}

auto Clock::frameTime() const -> frames {
  return frameTimer;
}

auto Clock::milli() const -> milliseconds {
  return millis();
}

auto Clock::time() const -> ClockTime {
  return {milli(), frameTimer};
}


auto Clock::stopTick() const -> void {
  auto stop = milli();
  auto time = stop - tickStart;
  if (time >= maxMsPerFrame) {
    return;
  }

  auto sleep = maxMsPerFrame - time;
  delay(sleep);
}

auto Clock::Init(frames fps) -> void {
  Instance().init(fps);
}

auto Clock::StartTick() -> void {
  Instance().startTick();
}

auto Clock::FrameTime() -> frames {
  return Instance().frameTime();
}

auto Clock::Milli() -> milliseconds {
  return Instance().milli();
}

auto Clock::Time() -> ClockTime {
  return Instance().time();
}

auto Clock::StopTick() -> void {
  Instance().stopTick();
}

auto Clock::micro() const -> microseconds {
  return micros();
}

}