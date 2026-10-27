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

template <size_t N>
class ArrayAnimation : public Animation {
public:
  explicit ArrayAnimation(std::array<AnimationFrame, N> frames);
  auto reset() -> void override;
  auto update(Duration delta) -> UpdateResult override;
  auto frameCount() const -> size_t override { return N; }
  auto isFinished() const -> bool { return mCurrentFrame >= N; }
  auto fastForward() -> void;

private:
  std::array<AnimationFrame, N> mFrames{};
  Timestamp mCurrentFrameElapsed{};
  u32 mCurrentFrame{};
};

template<size_t N>
ArrayAnimation<N>::ArrayAnimation(std::array<AnimationFrame, N> frames): mFrames(std::move(frames)) {
}

template<size_t N>
auto ArrayAnimation<N>::reset() -> void {
  mCurrentFrameElapsed = Timestamp::Zero();
  mCurrentFrame = 0;
}

template<size_t N>
auto ArrayAnimation<N>::update(Duration delta) -> UpdateResult {
  mCurrentFrameElapsed += delta;
  fastForward();

  if (isFinished()) {
    return UpdateResult::FINISHED;
  }

  mFrames[mCurrentFrame](mCurrentFrameElapsed.percentOf(mFrames[mCurrentFrame].duration()));
  return UpdateResult::RUNNING;
}

template<size_t N>
auto ArrayAnimation<N>::fastForward() -> void {
  while (!isFinished()) {
    auto currentFrame = &mFrames[mCurrentFrame];
    auto duration = currentFrame->duration();
    if (mCurrentFrameElapsed >= duration) {
      (*currentFrame)(1.0f);
      mCurrentFrameElapsed -= duration;
      ++mCurrentFrame;
    }
    else {
      break;
    }
  }
}
}

#endif //RGBLIB_ARRAYANIMATION_H
