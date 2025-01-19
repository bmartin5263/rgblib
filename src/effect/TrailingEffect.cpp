//
// Created by Brandon on 1/19/25.
//

#include "led/LEDChain.h"
#include "TrailingEffect.h"
#include "Parameters.h"
#include "ColorGenerator.h"

TrailingEffect::TrailingEffect(): speed(30) {

}

TrailingEffect::TrailingEffect(u16 speed): speed(speed) {

}

auto TrailingEffect::update() -> void {

}

auto TrailingEffect::draw(LEDChain& chain, ColorGenerator& colorGenerator) -> void {
  auto params = Parameters::dynamicEffect(chain, phase, speed);
  auto size = chain.size();
  for (u8 i = 0; i < length; ++i) {
    auto absolutePixel = (i + phase) % size;
    auto relativePixel = i;
    params.absolutePosition = absolutePixel;
    params.relativePosition = relativePixel;
    auto color = colorGenerator.generate(params);
    chain[absolutePixel] = color;
  }
}