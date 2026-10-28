//
// Created by Brandon on 8/15/26.
//

#include "ForFrame.h"

namespace rgb {

ForFrame::ForFrame(Duration interval, u32 iterations, const ForFrameFunction& function)
  : mInterval(interval),
    mIterations(iterations),
    mFunction(function) {
}

auto ForFrame::tryAdvance(FrameState& state) const -> FrameStatus {
  while (!ranAllIterations(state) && reachedNextIteration(state)) {
    mFunction(ForContext{state.iteration++, mIterations});
  }

  if (!ranAllIterations(state) || state.elapsed < totalDuration()) {
    return FrameStatus::RUNNING;
  }
  return FrameStatus::FINISHED;
}

auto ForFrame::tick(const FrameState&) const -> void {
}

auto ForFrame::totalDuration() const -> Duration {
  return mInterval * mIterations;
}

auto ForFrame::finished(FrameState& state) const -> void {
  state.elapsed -= totalDuration();
  state.iteration = 0;
}

auto ForFrame::ranAllIterations(const FrameState& state) const -> bool {
  // We might not be "finished" though if we are waiting for the last iteration to complete
  return state.iteration >= mIterations;
}

auto ForFrame::reachedNextIteration(const FrameState& state) const -> bool {
  return state.elapsed >= mInterval * state.iteration;
}
}
