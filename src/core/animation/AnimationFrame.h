//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_ANIMATIONFRAME_H
#define RGBLIB_ANIMATIONFRAME_H

#include "Func.h"
#include "Types.h"
#include "AnimationContext.h"

namespace rgb {

using AnimationFrameFunction = Consumer<const AnimationContext&>;

class AnimationFrame {
public:
  static constexpr auto DoNothing(const AnimationContext&) -> void {}

  AnimationFrame(Duration duration, const AnimationFrameFunction& function)
    : mDuration(duration),
      mFunction(function) {
  }

  AnimationFrame(Duration duration)
    : mDuration(duration),
      mFunction(DoNothing) {
  }

  static auto Wait(Duration duration) {
    return AnimationFrame{duration};
  }

  auto duration() const -> Duration;
  auto operator()(normal percentComplete) const -> void;

private:
  Duration mDuration;
  AnimationFrameFunction mFunction;

};
}

#endif //RGBLIB_ANIMATIONFRAME_H
