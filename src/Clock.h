//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_CLOCK_H
#define RGBLIB_CLOCK_H

#include "Types.h"
#include "ClockTime.h"

class Clock {
public:
  static auto Init(ft fps) -> void;

  static auto StartTick() -> void;
  static auto StopTick() -> void;

  static auto Milli() -> ms;
  static auto Frames() -> ft;
  static auto Time() -> ClockTime;

private:
  Clock() = default;
  auto init(ft targetFps) -> void;

  static auto Instance() -> Clock&;

  auto startTick() -> void;
  auto stopTick() const -> void;

  [[nodiscard]] auto milli() const -> ms;
  [[nodiscard]] auto frames() const -> ft;
  [[nodiscard]] auto time() const -> ClockTime;

  ft frameTime{};
  ft fpsCounter{};
  ms tickStart{};
  ms lastTime{};
  ft targetFps{};
};


#endif //RGBLIB_CLOCK_H
