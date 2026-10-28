//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_ARRAYANIMATION_H
#define RGBLIB_ARRAYANIMATION_H

#include <array>
#include <cstddef>

#include "Animation.h"
#include "Frames.h"

namespace rgb {

template <size_t N>
class ArrayAnimation : public Animation {
public:
  explicit ArrayAnimation(std::array<Frame, N> frames);
  auto reset() -> void override;
  auto update(Duration delta) -> UpdateResult override;
  auto frameCount() const -> size_t override { return N; }
  auto isFinished() const -> bool { return mCurrentFrame >= N; }
  auto fastForward() -> void;

  auto tryAdvance(const Frame& frame) -> FrameStatus;
  auto tick(const Frame& frame) -> void;
  auto finish(const Frame& frame) -> void;

private:
  std::array<Frame, N> mFrames{};
  FrameState mState{};
  u32 mCurrentFrame{};
};

template<size_t N>
ArrayAnimation<N>::ArrayAnimation(std::array<Frame, N> frames): mFrames(std::move(frames)) {
}

template<size_t N>
auto ArrayAnimation<N>::reset() -> void {
  mState = FrameState{};
  mCurrentFrame = 0;
}

template<size_t N>
auto ArrayAnimation<N>::update(Duration delta) -> UpdateResult {
  mState.elapsed += delta;
  fastForward();

  if (isFinished()) {
    return UpdateResult::FINISHED;
  }

  tick(mFrames[mCurrentFrame]);
  return UpdateResult::RUNNING;
}

template<size_t N>
auto ArrayAnimation<N>::fastForward() -> void {
  while (!isFinished() && tryAdvance(mFrames[mCurrentFrame]) == FrameStatus::FINISHED) {
    finish(mFrames[mCurrentFrame]);
    ++mCurrentFrame;
  }
}

template<size_t N>
auto ArrayAnimation<N>::tryAdvance(const Frame& frame) -> FrameStatus {
  return std::visit([this](const auto& f) { return f.tryAdvance(mState); }, frame);
}

template<size_t N>
auto ArrayAnimation<N>::tick(const Frame& frame) -> void {
  std::visit([this](const auto& f) { f.tick(mState); }, frame);
}

template<size_t N>
auto ArrayAnimation<N>::finish(const Frame& frame) -> void {
  std::visit([this](const auto& f) { f.finished(mState); }, frame);
}
}

#endif //RGBLIB_ARRAYANIMATION_H
