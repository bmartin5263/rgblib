//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_TRAILINGEFFECT_H
#define RGBLIB_TRAILINGEFFECT_H

#include "core/Types.h"

class LEDChain;
class ColorGenerator;
class TrailingEffect {
public:
  TrailingEffect();
  TrailingEffect(u16 speed);
  auto update() -> void;
  auto draw(LEDChain& chain, ColorGenerator& colorGenerator) -> void;

  auto getSpeed() -> u16;
  auto setSpeed(u16 value) -> void;

private:
  u16 speed{30};
  u16 phase{0};
  u16 length{10};
};


#endif //RGBLIB_TRAILINGEFFECT_H
