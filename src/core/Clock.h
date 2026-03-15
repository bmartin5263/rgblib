//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_CLOCK_H
#define RGBLIB_CLOCK_H

#include "Types.h"
#include "System.h"
#include "Log.h"

namespace rgb {

class Clock {
public:
  auto nextFrame() -> void;

  static auto NextFrame() -> void { Instance().nextFrame(); }
  static auto Start(frames_t fps) -> void { Instance().start(fps); }
  static auto Now() -> Timestamp { return Timestamp{System::MicroTime()}; }
  static auto Fps() -> uint { return Instance().fps(); }

private:

  static auto Instance() -> Clock&;
  auto start(frames_t fps) -> void;
  auto fps() const -> uint;

  frames_t mFrames{};
  frames_t mFpsCounter{};
  frames_t mLastFps{};
  frames_t mTargetFps; // for detecting low FPS
  u64 mNextFrame{};
  microseconds_t mTickStart{};
  microseconds_t mLastFrameRateCheck{};
  microseconds_t mMaxMillisecondsPerFrame;
  microseconds_t mDelta{};
  uint lastWakeTime{xTaskGetTickCount()};
  u64 frequency{pdMS_TO_TICKS(4)};
  bool lowFpsDetected{};
};

}


#endif //RGBLIB_CLOCK_H
