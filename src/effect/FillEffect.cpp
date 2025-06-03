//
// Created by Brandon on 4/14/25.
//

#include "FillEffect.h"
#include "PixelList.h"
#include "Clock.h"
#include "Enumerate.h"

namespace rgb {

auto FillEffect::draw(PixelList& chain) -> void {
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