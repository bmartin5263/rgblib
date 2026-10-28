//
// Created by Brandon on 8/15/26.
//

#include "Frames.h"

namespace rgb {

auto Frames::Wait(Duration duration) -> Frame {
  return TimedFrame{duration, TimedFrame::DoNothing};
}

auto Frames::Once(const TimedFrameFunction& function) -> Frame {
  return TimedFrame{Duration::Zero(), function};
}

auto Frames::Of(Duration duration, const TimedFrameFunction& function) -> Frame {
  return TimedFrame{duration, function};
}

auto Frames::For(Duration interval, u32 iterations, const ForFrameFunction& function) -> Frame {
  return ForFrame{interval, iterations, function};
}

auto Frames::While(const Predicate& condition, const WhileFrameFunction& function) -> Frame {
  return WhileFrame{condition, function};
}

}
