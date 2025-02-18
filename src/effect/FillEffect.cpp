//
// Created by Brandon on 1/8/25.
//

#include "FillEffect.h"
#include "led/LEDChain.h"
#include "Clock.h"

namespace rgb {

auto FillEffect::draw(LEDChain& chain) -> void {
  auto time = Clock::Time();
  auto params = FillEffectParameters {
    time,
    &chain,
    0
  };
  for (u16 i = 0; i < chain.size(); ++i) {
    params.position = i;
    auto color = colorGenerator(params);
    chain[i] = color;
  }
}

auto FillEffect::setColorGenerator(const FillEffectColorGenerator& value) -> FillEffect& {
  colorGenerator = std::move(value);
  return *this;
}

auto FillEffect::getColorGenerator() -> FillEffectColorGenerator {
  return colorGenerator;
}

auto FillEffect::defaultGenerator(const FillEffectParameters& params) -> Color {
  return Color::MAGENTA();
}

}