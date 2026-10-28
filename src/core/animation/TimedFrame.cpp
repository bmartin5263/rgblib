//
// Created by Brandon on 8/15/26.
//

#include "TimedFrame.h"

namespace rgb {

TimedFrame::TimedFrame(Duration duration, const TimedFrameFunction& function)
  : mDuration(duration),
    mFunction(function) {
}

auto TimedFrame::tryAdvance(FrameState& state) const -> FrameStatus {
  if (isFinished(state)) {
    mFunction(TimedContext{1.0f});
    finished(state);
    return FrameStatus::FINISHED;
  }
  return FrameStatus::RUNNING;
}

auto TimedFrame::tick(const FrameState& state) const -> void {
  mFunction(TimedContext{state.elapsed.percentOf(mDuration)});
}

auto TimedFrame::isFinished(const FrameState& state) const -> bool {
  return state.elapsed >= mDuration;
}

auto TimedFrame::finished(FrameState& state) const -> void {
  state.elapsed -= mDuration;
}
}
