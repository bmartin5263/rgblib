//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_PARAMETERS_H
#define RGBLIB_PARAMETERS_H

#include "Types.h"

class LEDChain;
struct Parameters {
  u32 millis;
  u32 frames;
  i16 phase;
  i16 speed;
  LEDChain* ledChain;
  u16 absolutePosition;
  u16 relativePosition;

  static auto staticEffect(LEDChain& ledChain) -> Parameters;
  static auto dynamicEffect(LEDChain& ledChain, u16 phase, u16 speed) -> Parameters;
};


#endif //RGBLIB_PARAMETERS_H
