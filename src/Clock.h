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
  static auto Init(frames fps) -> void;

  static auto StartTick() -> void;
  static auto StopTick() -> void;

  static auto Micro() -> microseconds;
  static auto Milli() -> milliseconds;
  static auto FrameTime() -> frames;
  static auto Time() -> ClockTime;

private:
  Clock() = default;
  auto init(frames targetFps) -> void;

  static auto Instance() -> Clock&;

  auto startTick() -> void;
  auto stopTick() const -> void;

  [[nodiscard]] auto milli() const -> milliseconds ;
  [[nodiscard]] auto frameTime() const -> frames;
  [[nodiscard]] auto micro() const -> microseconds ;
  [[nodiscard]] auto time() const -> ClockTime;

  frames frameTimer{};
  frames fpsCounter{};
  milliseconds tickStart{};
  milliseconds lastTime{};
  milliseconds maxMsPerFrame{};
};

}


#endif //RGBLIB_CLOCK_H
