//
// Created by Brandon on 1/5/25.
//

#include "Debug.h"
#include "Color.h"
#include "PixelList.h"

namespace rgb {

auto Debug::trigger() -> void {
  triggered = true;
}

auto Debug::trigger(Color color) -> void {
  triggerColor = color;
  trigger();
}

auto Debug::recover() -> void {
  triggered = false;
}

auto Debug::update() -> void {
}

auto Debug::draw() -> void {
  if (debugChain != nullptr && triggered) {
    debugChain->fill(triggerColor);
  }
}

auto Debug::setDebugChain(PixelList* chain) -> void {
  this->debugChain = chain;
}

auto Debug::Instance() -> Debug& {
  static Debug instance;
  return instance;
}

}