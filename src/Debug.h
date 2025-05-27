//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_DEBUG_H
#define RGBLIB_DEBUG_H

#include "Color.h"

namespace rgb {

class LEDChain;
class Debug {
public:
  static auto Trigger() -> void { Instance().trigger(); }
  static auto Trigger(Color color) -> void { Instance().trigger(color); }
  static auto Recover() -> void { Instance().recover(); }
  static auto Update() -> void { Instance().update(); }
  static auto Draw() -> void { Instance().draw(); }
  static auto SetDebugChain(LEDChain* chain) -> void { Instance().setDebugChain(chain); }

private:
  Debug() = default;
  Debug(const Debug& rhs) = default;
  Debug(Debug&& rhs) noexcept = default;
  Debug& operator=(const Debug& rhs) = default;
  Debug& operator=(Debug&& rhs) noexcept = default;
  ~Debug() = default;

  static auto Instance() -> Debug&;
  auto trigger() -> void;
  auto trigger(Color color) -> void;
  auto recover() -> void;
  auto update() -> void;
  auto draw() -> void;
  auto setDebugChain(LEDChain* chain) -> void;

  LEDChain* debugChain{nullptr};
  Color triggerColor{Color::CYAN(.01f)};
  bool triggered{false};
};

}

#endif //RGBLIB_DEBUG_H
