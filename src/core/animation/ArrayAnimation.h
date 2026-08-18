//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_ARRAYANIMATION_H
#define RGBLIB_ARRAYANIMATION_H

#include <array>
#include <cstddef>

#include "Animation.h"
#include "AnimationFrame.h"

namespace rgb {

template <size_t FRAMES>
class ArrayAnimation : public Animation{
public:
  explicit ArrayAnimation(std::array<AnimationFrame, FRAMES> frames);
  auto reset() -> void override;
  auto update(Duration delta) -> bool override;
  auto frameCount() const -> size_t override { return FRAMES; }

private:
  std::array<AnimationFrame, FRAMES> mFrames{};
  Timestamp mCurrentFrameElapsed{};
  u32 mCurrentFrame{};

};

template<size_t FRAMES>
ArrayAnimation<FRAMES>::ArrayAnimation(std::array<AnimationFrame, FRAMES> frames): mFrames(std::move(frames)) {
}

template<size_t FRAMES>
auto ArrayAnimation<FRAMES>::reset() -> void {
  mCurrentFrameElapsed = Timestamp{};
  mCurrentFrame = 0;
}

template<size_t FRAMES>
auto ArrayAnimation<FRAMES>::update(Duration delta) -> bool {
  mCurrentFrameElapsed += delta;

  // A large delta can span multiple frames; walk through each one so its
  // function still fires instead of jumping straight to the landing frame.
  while (mCurrentFrame < FRAMES && mCurrentFrameElapsed >= mFrames[mCurrentFrame].duration()) {
    mFrames[mCurrentFrame](1.0f);
    mCurrentFrameElapsed -= mFrames[mCurrentFrame].duration();
    ++mCurrentFrame;
  }

  if (mCurrentFrame >= FRAMES) {
    return false; // animation is over
  }

  mFrames[mCurrentFrame](mCurrentFrameElapsed.percentOf(mFrames[mCurrentFrame].duration()));
  return true; // continue the animation
}

}

#endif //RGBLIB_ARRAYANIMATION_H
