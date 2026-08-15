//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_ARRAYANIMATION_H
#define RGBLIB_ARRAYANIMATION_H

#include <array>

#include "Animation.h"
#include "AnimationFrame.h"

namespace rgb {

template <u32 FRAMES>
class ArrayAnimation : public Animation{
public:
  ArrayAnimation(std::array<AnimationFrame, FRAMES> frames);
  auto update(Timestamp now) -> bool override;
  auto frameCount() const -> u32 override { return FRAMES; }

private:
  std::array<AnimationFrame, FRAMES> mFrames{};

};

template<u32 FRAMES>
ArrayAnimation<FRAMES>::ArrayAnimation(std::array<AnimationFrame, FRAMES> frames): mFrames(std::move(frames)) {
}

template<u32 FRAMES>
auto ArrayAnimation<FRAMES>::update(Timestamp now) -> bool {
  auto time = Timestamp{};
  for (auto& frame : mFrames) {
    auto frameStart = time;
    time += frame.duration();
    if (now < time) {
      frame((now - frameStart).percentOf(frame.duration()));
      return true;
    }
  }
  return false;
}
}

#endif //RGBLIB_ARRAYANIMATION_H
