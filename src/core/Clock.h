//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_CLOCK_H
#define RGBLIB_CLOCK_H

#include "Types.h"

class Clock {
public:
  auto initialize(u16 targetFps) -> void;

  auto startTick() -> void;
  auto stopTick() -> void;

  auto milli() -> u32;
  auto frames() -> u32;

  static auto Instance() -> Clock&;
private:
  Clock() = default;

  u32 _globalFrame{};
  u32 globalFpsCounter{};
  u32 tickStart{};
  u32 lastTimeMs{};
  u16 targetFps{};
};


#endif //RGBLIB_CLOCK_H
