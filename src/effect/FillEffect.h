//
// Created by Brandon on 1/8/25.
//

#ifndef RGBLIB_FILLEFFECT_H
#define RGBLIB_FILLEFFECT_H

#include <functional>
#include "Types.h"
#include "Color.h"
#include "ClockTime.h"

#define Generator [](auto& params)

class LEDChain;

struct FillEffectParameters {
  ClockTime time;
  LEDChain* ledChain;
  u16 position;
};

using FillEffectColorGenerator = std::function<Color(const FillEffectParameters&)>;


class FillEffect {
public:
  auto draw(LEDChain& chain) -> void;

  auto getColorGenerator() -> FillEffectColorGenerator;
  auto setColorGenerator(const FillEffectColorGenerator& value) -> FillEffect&;

private:
  static auto defaultGenerator(const FillEffectParameters& params) -> Color;

  FillEffectColorGenerator colorGenerator{defaultGenerator};

};


#endif //RGBLIB_FILLEFFECT_H
