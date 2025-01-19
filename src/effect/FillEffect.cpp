//
// Created by Brandon on 1/8/25.
//

#include "FillEffect.h"
#include "ColorGenerator.h"
#include "led/LEDChain.h"

void FillEffect::draw(LEDChain& chain, ColorGenerator& colorGenerator) {
  auto params = Parameters::staticEffect(chain);
  for (u16 i = 0; i < chain.size(); ++i) {
    params.absolutePosition = i;
    params.relativePosition = i;
    auto color = colorGenerator.generate(params);
    chain[i] = color;
  }
}