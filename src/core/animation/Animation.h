//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_ANIMATION_H
#define RGBLIB_ANIMATION_H
#include "Types.h"


namespace rgb {
class Animation {
public:
  Animation() = default;
  Animation(const Animation& rhs) = default;
  Animation(Animation&& rhs) noexcept = default;
  Animation& operator=(const Animation& rhs) = default;
  Animation& operator=(Animation&& rhs) noexcept = default;
  virtual ~Animation() = default;

  virtual auto update(Duration delta) -> bool = 0;
  virtual auto reset() -> void = 0;
  virtual auto frameCount() const -> u32 = 0;
};
}

#endif //RGBLIB_ANIMATION_H
