//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_DEBUG_H
#define RGBLIB_DEBUG_H

#include "Assertions.h"

namespace rgb {

class LEDChain;
class Driver;
class Debug {
public:
  auto trigger(bool value) -> void;
  auto update() -> void;
  auto setDebugChain(LEDChain* chain) -> void;

  static auto Instance() -> Debug&;
private:
  Debug() = default;

  LEDChain* debugChain{nullptr};
  bool triggered{false};

};

}


#endif //RGBLIB_DEBUG_H
