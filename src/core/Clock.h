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
  explicit Clock(frames_t fps): mTargetFps(fps), mMaxMillisecondsPerFrame(1000 / fps)  {}

  auto startFrame() -> void;
  auto endFrame() -> void;

  auto printStats() -> void;

  static auto Now() -> Timestamp;

private:

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
