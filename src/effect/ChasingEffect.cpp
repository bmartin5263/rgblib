//
// Created by Brandon on 8/17/25.
//

#include "ChasingEffect.h"
#include "Clock.h"

namespace rgb {

auto ChasingEffect::reset() -> void {
  position = 0;
  nextMoveTime = Clock::Now();
}

auto ChasingEffect::update() -> void {
  if (Clock::Now() >= nextMoveTime) {
    step();
    nextMoveTime = Clock::Now() + delay;
  }
}

auto ChasingEffect::step() -> void {
  position += 1;
}

auto ChasingEffect::draw(PixelList& pixels) -> void {
  if (std::holds_alternative<normal>(trailLength.variant)) {

  }
  else {

  }
}

auto ChasingEffect::draw(Iterable<PixelList*> pixelLists) -> void {

}

}