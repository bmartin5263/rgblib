//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_BREATHEEFFECT_H
#define RGBLIB_BREATHEEFFECT_H

#include "Types.h"
#include "Color.h"

class LEDChain;
class ColorGenerator;
class BreatheEffect {
public:
  auto update() -> void;
  auto draw(LEDChain& chain) -> void;

  auto getHighColor() -> Color;
  auto setHighColor(const Color& value) -> BreatheEffect&;

  auto getLowColor() -> Color;
  auto setLowColor(const Color& value) -> BreatheEffect&;

  auto getHighTime() -> u16;
  auto setHighTime(u16 value) -> BreatheEffect&;

  auto getLowTime() -> u16;
  auto setLowTime(u16 value) -> BreatheEffect&;

  auto getSpeed() -> u16;
  auto setSpeed(u16 value) -> BreatheEffect&;

private:
  Color highColor{Color::RED()};
  Color lowColor{Color::OFF()};
  u16 highTime{30};
  u16 lowTime{30};
  u16 speed{30};
  float phase{0.0f}; // 0.0 - 1.0
};


#endif //RGBLIB_BREATHEEFFECT_H
