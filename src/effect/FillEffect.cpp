//
// Created by Brandon on 4/14/25.
//

#include "FillEffect.h"
#include "PixelList.h"
#include "Clock.h"
#include "Brightness.h"
#include "Enumerate.h"

namespace rgb {

auto FillEffect::draw(Timestamp now, PixelList& pixels) -> void {
  auto params = FillEffectShaderParameters {
    .now = Clock::Now(),
    .length = pixels.length(),
    .position = 0,
    .brightness = Brightness::GetBrightness(brightness)
  };
  for (int i = 0; i < pixels.length(); ++i) {
    auto pixel = pixels.get(i);
    params.position = i;
    pixels.set(i, shader(pixel, params));
  }
}

}