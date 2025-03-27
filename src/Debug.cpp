//
// Created by Brandon on 1/5/25.
//

#include "Debug.h"
#include "Color.h"
#include "led/LEDChain.h"

namespace rgb {

auto Debug::trigger(bool value) -> void {
  triggered = value;
}

auto Debug::update() -> void {
  if (debugChain != nullptr && triggered) {
    debugChain->fill(Color::RED());
  }
}

auto Debug::draw() -> void {
  if (debugChain != nullptr && triggered) {
    debugChain->fill(Color::RED(.01));
  }
}

auto Debug::setDebugChain(LEDChain* chain) -> void {
  this->debugChain = chain;
}

auto Debug::Instance() -> Debug& {
  static Debug instance;
  return instance;
}

}