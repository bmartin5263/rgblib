//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_ANIMATIONHANDLE_H
#define RGBLIB_ANIMATIONHANDLE_H

#include "Types.h"

namespace rgb {

struct AnimationNode;
class AnimationHandle {
public:
  AnimationHandle();
  explicit AnimationHandle(AnimationNode* node);
  AnimationHandle(const AnimationHandle& rhs) = delete;
  AnimationHandle(AnimationHandle&& rhs) noexcept;
  AnimationHandle& operator=(const AnimationHandle& rhs) = delete;
  AnimationHandle& operator=(AnimationHandle&& rhs) noexcept;
  ~AnimationHandle();

  // Release ownership without stopping the effect
  auto detach() -> void;

  // Release ownership and stop the effect
  auto stop() -> void;

  auto isRunning() const -> bool;

  auto operator==(const AnimationHandle& rhs) const -> bool {
    return node == rhs.node && handleId == rhs.handleId;
  }

  auto operator!=(const AnimationHandle& rhs) const -> bool {
    return !(*this == rhs);
  }

  uint handleId;
  AnimationNode* node;
};

}

#endif //RGBLIB_ANIMATIONHANDLE_H
