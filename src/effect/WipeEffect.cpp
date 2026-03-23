//
// Created by Brandon on 8/17/25.
//

#include <cmath>
#include "WipeEffect.h"
#include "Clock.h"
#include "Brightness.h"

namespace rgb {

auto WipeEffect::draw(Timestamp now, PixelList& pixels) -> void {
  auto pixelLength = pixels.length();

  Duration duration;
  if (progression.durationIsDelay) {
    duration = Duration{progression.duration.value * pixelLength};
  }
  else {
    duration = progression.duration;
  }

  auto headPercent = now.percentOf(Timestamp{duration.value});
  float wipeCycle;
  float wipePercent = modff(headPercent, &wipeCycle);

  auto wipeLength = static_cast<uint>(static_cast<float>(pixelLength) * wipePercent); // round down
  auto params = ShaderParameters {
    .now = now,
    .duration = progression.duration,
    .wipeLength = wipeLength,
    .wipeCycle = static_cast<uint>(wipeCycle),
    .pixelPosition = 0,
    .positionRatio = 0.0f,
    .brightness = Brightness::GetBrightness(brightness)
  };

  for (auto pixelPosition = 0; pixelPosition < pixels.length(); ++pixelPosition) {
    params.positionRatio = static_cast<float>(pixelPosition) / static_cast<float>(pixels.length());
    params.pixelPosition = pixelPosition;
    pixels.set(pixelPosition, shader(pixels.get(pixelPosition), params));
  }
}

}