//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_CLOCK_H
#define RGBLIB_CLOCK_H

#include "Types.h"
#include "ClockTime.h"

namespace rgb {

class Clock {
public:
  static auto Start(frames_t fps) -> void;

  static auto StartTick() -> void;
  static auto StopTick() -> void;

  static auto Now() -> Timestamp;
  static auto Delta() -> Duration;
  static auto Milli() -> milliseconds_t;
  static auto Frames() -> frames_t;
  static auto Fps() -> frames_t;

private:
  Clock() = default;
  auto start(frames_t targetFps) -> void;

  static auto Instance() -> Clock&;

  auto startTick() -> void;
  auto stopTick() -> void;

  [[nodiscard]] auto milli() const -> milliseconds_t ;
  [[nodiscard]] auto frames() const -> frames_t;
  [[nodiscard]] auto delta() const -> Duration;
  [[nodiscard]] auto fps() const -> frames_t;

  frames_t mFrames{};
  frames_t mFpsCounter{};
  frames_t mLastFps{};
  frames_t mTargetFps{};
  microseconds_t mTickStart{};
  microseconds_t mLastFrameRateCheck{};
  microseconds_t mMaxMicrosPerFrame{};
  microseconds_t mDelta{};
};

}


#endif //RGBLIB_CLOCK_H
