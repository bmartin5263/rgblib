//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_TRAILINGEFFECT_H
#define RGBLIB_TRAILINGEFFECT_H

#include <functional>
#include "Types.h"
#include "Color.h"

namespace rgb {

class LEDChain;

struct TrailingEffectParameters {
  u32 millis;
  u32 frames;
  i16 phase;
  i16 speed;
  LEDChain* ledChain;
  u16 absolutePosition;
  u16 relativePosition;
};

using TrailingEffectColorGenerator = std::function<Color(const TrailingEffectParameters&)>;

class TrailingEffect {
public:
  auto update() -> void;
  auto draw(LEDChain& chain) -> void;

  auto getSpeed() const -> u16;
  auto setSpeed(u16 value) -> TrailingEffect&;

  auto getLength() const -> u16;
  auto setLength(u16 value) -> TrailingEffect&;

  auto getColorGenerator() -> TrailingEffectColorGenerator;
  auto setColorGenerator(const TrailingEffectColorGenerator& value) -> TrailingEffect&;

private:
  static auto defaultGenerator(const TrailingEffectParameters& params) -> Color;

  TrailingEffectColorGenerator colorGenerator{defaultGenerator};
  u16 speed{30};
  u16 phase{0};
  u16 length{10};
};

}


#endif //RGBLIB_TRAILINGEFFECT_H
