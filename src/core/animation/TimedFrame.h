//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_TIMEDFRAME_H
#define RGBLIB_TIMEDFRAME_H

#include "Func.h"
#include "Types.h"
#include "AnimationContext.h"
#include "FrameState.h"

namespace rgb {

using TimedFrameFunction = Consumer<const TimedContext&>;

class TimedFrame {
public:
  static constexpr auto DoNothing(const TimedContext&) -> void {}

  TimedFrame(Duration duration, const TimedFrameFunction& function);

  auto tryAdvance(FrameState& state) const -> FrameStatus;
  auto tick(const FrameState& state) const -> void;
  auto finished(FrameState& state) const -> void;

private:
  auto isFinished(const FrameState& state) const -> bool;

  Duration mDuration;
  TimedFrameFunction mFunction;
};

}

#endif //RGBLIB_TIMEDFRAME_H
