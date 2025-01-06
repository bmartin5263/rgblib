//
// Created by Brandon on 1/5/25.
//

#include "Debug.h"
#include "led/Color.h"
#include "led/LEDChain.h"

auto Debug::trigger(bool value) -> void {
  triggered = value;
}

auto Debug::update() -> void {
  if (debugChain != nullptr && triggered) {
    debugChain->set(0, Color::RED());
  }
}

auto Debug::setDebugChain(LEDChain* chain) -> void {
  this->debugChain = chain;
}

auto Debug::Instance() -> Debug& {
  static Debug instance;
  return instance;
}
