//
// Created by Brandon on 1/19/25.
//

#include "led/LEDChain.h"
#include "TrailingEffect.h"

#include <utility>
#include "Clock.h"

namespace rgb {

auto TrailingEffect::update() -> void {

}

auto TrailingEffect::draw(LEDChain& chain) -> void {
  auto clockTime = Clock::Time();
  auto params = TrailingEffectParameters {
    clockTime.millis,
    clockTime.frames,
    static_cast<i16>(phase),
    static_cast<i16>(speed),
    &chain,
    0,
    0
  };
  u16 size = chain.size();
  u8 replicas = 1;

  for (u8 replica = 0; replica < replicas; ++replica) {
    for (u16 i = 0; i < length; ++i) {
      auto absolutePixel = (i + phase) % size;
      auto relativePixel = i;
      params.absolutePosition = absolutePixel;
      params.relativePosition = relativePixel;
      auto color = colorGenerator(params);
      chain[absolutePixel] = color;
    }
  }
}

auto TrailingEffect::setSpeed(u16 value) -> TrailingEffect& {
  speed = value;
  return *this;
}

auto TrailingEffect::getSpeed() const -> u16 {
  return speed;
}

auto TrailingEffect::setColorGenerator(const TrailingEffectColorGenerator& value) -> TrailingEffect& {
  colorGenerator = std::move(value);
  return *this;
}

auto TrailingEffect::getColorGenerator() -> TrailingEffectColorGenerator {
  return colorGenerator;
}

auto TrailingEffect::setLength(u16 value) -> TrailingEffect& {
  length = value;
  return *this;
}

auto TrailingEffect::getLength() const -> u16 {
  return length;
}

auto TrailingEffect::defaultGenerator(const TrailingEffectParameters& params) -> Color {
  return Color::MAGENTA();
}

}