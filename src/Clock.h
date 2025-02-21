//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_CLOCK_H
#define RGBLIB_CLOCK_H

#include "Types.h"
#include "ClockTime.h"

namespace rgb {

class Clock {
public:
  static auto Init(frame_time fps) -> void;

  static auto StartTick() -> void;
  static auto StopTick() -> void;

  static auto Micro() -> microseconds;
  static auto Milli() -> milliseconds;
  static auto Frames() -> frame_time;
  static auto Time() -> ClockTime;

private:
  Clock() = default;
  auto init(frame_time targetFps) -> void;

  static auto Instance() -> Clock&;

  auto startTick() -> void;
  auto stopTick() const -> void;

  [[nodiscard]] auto milli() const -> milliseconds ;
  [[nodiscard]] auto frames() const -> frame_time;
  [[nodiscard]] auto micro() const -> microseconds ;
  [[nodiscard]] auto time() const -> ClockTime;

  frame_time frameTime{};
  frame_time fpsCounter{};
  milliseconds tickStart{};
  milliseconds lastTime{};
  milliseconds maxMsPerFrame{};
};

}


#endif //RGBLIB_CLOCK_H
