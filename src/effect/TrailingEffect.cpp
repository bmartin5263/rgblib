//
// Created by Brandon on 4/15/25.
//

#include "TrailingEffect.h"
#include "Clock.h"
#include "PixelList.h"

using namespace rgb;

auto TrailingEffect::init() -> void {
  pixel = -startBuffer;
  nextMoveTime = Clock::Now() + speed;
}

auto TrailingEffect::update() -> void {
  auto now = Clock::Now();
  if (now >= nextMoveTime) {
    move();
    nextMoveTime = now + speed;
  }
}

auto TrailingEffect::draw(PixelList& chain) -> void {
  auto chainLength = chain.getSize();
  auto trailLength = static_cast<u16>(chainLength * trailRatio);
  auto now = Clock::Now();

  auto params = TrailingEffectShaderParameters {
    .now = now,
    .speed = speed,
    .trailLength = trailLength
  };

  for (int i = 0; i < trailLength; ++i) {
    auto p = pixel - i;
    if (p < 0) {
      break;
    }
    if (isRing ? p > chainLength * cycles : p >= chainLength * cycles) {
      continue;
    }
    auto led = p % (chainLength + endBuffer);
    if (led < chainLength + 1) {
      led = (led + offset) % chainLength;
      params.relativePosition = i;
      params.positionRatio = i / static_cast<float>(trailLength);
      params.absolutePosition = led;
      shader(chain[led], params);
    }
  }
}

auto TrailingEffect::move() -> void {
  pixel += 1;
}