//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_ANIMATIONS_H
#define RGBLIB_ANIMATIONS_H

#include "PriorityNodePool.h"
#include "AnimationHandle.h"
#include "AnimationNode.h"

#ifndef RGB_MAX_ANIMATIONS
#define RGB_MAX_ANIMATIONS 7
#endif

namespace rgb {

class Animation;
class Animations : public PriorityNodePool<AnimationNode, RGB_MAX_ANIMATIONS> {
public:
  static auto Initialize() -> void;
  [[nodiscard]]
  static auto Start(Animation& animation, bool loop = false) -> AnimationHandle;
  static auto Stop(Animation& animation) -> void;
  static auto StopAll() -> void;

  template<typename... Args>
  static auto Stop(Animation& first, Args&... rest) -> void {
    auto& instance = Instance();
    instance.stop(first);
    (instance.stop(rest), ...);
  }
  static auto Update() -> void;
  static auto ActiveCount() -> uint;
  static auto PeakCount() -> uint;
  static auto Instance() -> Animations&;

  Animations();
  Animations(const Animations& rhs) = default;
  Animations(Animations&& rhs) noexcept = default;
  Animations& operator=(const Animations& rhs) = default;
  Animations& operator=(Animations&& rhs) noexcept = default;
  ~Animations() = default;

private:
  Timestamp startTime{};

  auto initialize() -> void;
  auto start(Animation& animation, bool loop) -> AnimationHandle;
  auto stop(Animation& animation) -> void;
  auto stopAll() -> void;
  auto update() -> void;

  auto processAdditions(Timestamp now) -> void;
};


}



#endif //RGBLIB_ANIMATIONS_H
