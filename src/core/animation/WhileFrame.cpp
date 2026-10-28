//
// Created by Brandon on 8/15/26.
//

#include "WhileFrame.h"

namespace rgb {

WhileFrame::WhileFrame(const Predicate& condition, const WhileFrameFunction& function)
  : mCondition(condition),
    mFunction(function) {
}

auto WhileFrame::tryAdvance([[maybe_unused]] FrameState& state) const -> FrameStatus {
  if (mCondition()) {
    return FrameStatus::RUNNING;
  }
  return FrameStatus::FINISHED;
}

auto WhileFrame::tick(const FrameState& state) const -> void {
  mFunction(WhileContext{Duration{state.elapsed.value}});
}

auto WhileFrame::finished(FrameState& state) -> void {
  state.reset();
}
}
