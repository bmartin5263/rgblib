//
// Created by Brandon on 4/14/25.
//

#include "FillEffect.h"
#include "led/LEDChain.h"
#include "time/Clock.h"
#include "Enumerate.h"

namespace rgb {

auto FillEffect::draw(LEDChain& chain) -> void {
  auto params = FillEffectShaderParameters {
    .now = Clock::Now(),
    .length = chain.getSize(),
    .position = 0
  };
  for (auto [i, led] : enumerate(chain)) {
    params.position = i;
    shader(led, params);
  }
}

}