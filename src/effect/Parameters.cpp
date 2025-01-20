//
// Created by Brandon on 1/19/25.
//

#include "Parameters.h"
#include "Clock.h"

auto Parameters::staticEffect(LEDChain& ledChain) -> Parameters {
  auto clockTime = Clock::Instance().time();
  return {
    clockTime.millis,
    clockTime.frames,
    -1,
    -1,
    &ledChain,
    0,
    0
  };
}

auto Parameters::dynamicEffect(LEDChain& ledChain, u16 phase, u16 speed) -> Parameters {
  auto clockTime = Clock::Instance().time();
  return {
    clockTime.millis,
    clockTime.frames,
    static_cast<i16>(phase),
    static_cast<i16>(speed),
    &ledChain,
    0,
    0
  };
}