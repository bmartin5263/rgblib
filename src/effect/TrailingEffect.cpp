//
// Created by Brandon on 4/15/25.
//

#include "TrailingEffect.h"
#include "time/Clock.h"
#include "led/LEDChain.h"

using namespace rgb;

auto TrailingEffect::init() -> void {
  pixel = 0;
  nextMoveTime = Timestamp(0);
}

auto TrailingEffect::update() -> void {
  auto now = Clock::Now();
  if (now >= nextMoveTime) {
    move();
    nextMoveTime = now + speed;
  }
}

auto TrailingEffect::draw(LEDChain& chain) -> void {
  auto chainLength = chain.getSize();
  auto trailLength = static_cast<u16>(chainLength * trailRatio);
  auto now = Clock::Now();

  auto params = TrailingEffectShaderParameters {
    .now = now,
    .speed = speed,
    .trailLength = trailLength
  };
  if (continuous) {
    for (int i = 0; i < trailLength; ++i) {
      auto led = (pixel + i) % (chainLength + endBuffer);
      if (led < chainLength + 1) {
        led = (led + offset) % chainLength;
        params.relativePosition = i;
        params.positionRatio = i / static_cast<float>(trailLength);
        params.absolutePosition = led;
        chain[led] = shader(params);
      }
    }
  }
  else {
    for (int i = 0; i < trailLength; ++i) {
      auto led = (pixel + i + 1) - ((i32) trailLength);
      if (led < chainLength + 1) {
        led = (led + offset) % chainLength;
        params.relativePosition = i;
        params.absolutePosition = led;
        chain[led] = shader(params);
      }
    }
  }
}

auto TrailingEffect::move() -> void {
  pixel += 1;
}