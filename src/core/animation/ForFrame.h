//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_FORFRAME_H
#define RGBLIB_FORFRAME_H

#include "Func.h"
#include "Types.h"
#include "AnimationContext.h"
#include "FrameState.h"

namespace rgb {

using ForFrameFunction = Consumer<const ForContext&>;

class ForFrame {
public:
  ForFrame(Duration interval, u32 iterations, const ForFrameFunction& function);

  auto tryAdvance(FrameState& state) const -> FrameStatus;
  auto tick(const FrameState& state) const -> void;
  auto totalDuration() const -> Duration;
  auto finished(FrameState& state) const -> void;

private:
  auto ranAllIterations(const FrameState& state) const -> bool;
  auto reachedNextIteration(const FrameState& state) const -> bool;

  Duration mInterval;
  u32 mIterations;
  ForFrameFunction mFunction;
};

}

#endif //RGBLIB_FORFRAME_H
