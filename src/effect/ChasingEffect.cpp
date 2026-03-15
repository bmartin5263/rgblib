//
// Created by Brandon on 8/17/25.
//

#include "ChasingEffect.h"
#include "Clock.h"

namespace rgb {

auto ChasingEffect::draw(Timestamp now, PixelList& pixels) -> void {
  auto pixelLength = pixels.length();

  uint actualTrailLength = trailLength.getUnits(pixels);

  auto params = ShaderParameters {
    .now = now,
    .duration = progression.duration,
    .trailLength = actualTrailLength,
    .pixelPosition = 0,
    .trailPosition = 0,
    .positionRatio = 0.0f,
    .brightness = Brightness::GetBrightness(brightness)
  };

  Duration duration;
  if (progression.isDelay) {
    duration = Duration{progression.duration.value * pixelLength};
  }
  else {
    duration = progression.duration;
  }

  auto headPercent = now.percentOf(Timestamp{duration.value});
  auto effectPosition = static_cast<ulong>(static_cast<float>(pixelLength) * headPercent); // round down
  params.cycle = static_cast<uint>(headPercent);

  if (buildup) {
    for (auto trailPosition = 0; trailPosition < actualTrailLength; ++trailPosition) {
      if (trailPosition > effectPosition) {
        // Anything before effectPosition is not drawn
        break;
      }
      auto cycle = (effectPosition - trailPosition) / pixelLength;
      auto pixelPosition = (effectPosition - trailPosition + shift) % pixelLength; // draw head first
      params.trailPosition = trailPosition;
      params.positionRatio = static_cast<float>(actualTrailLength - trailPosition) / static_cast<float>(actualTrailLength);
      params.pixelPosition = pixelPosition;
      params.cycle = cycle;
      pixels.set(pixelPosition, shader(pixels.get(pixelPosition), params));
    }
  }
  else {
    for (auto trailPosition = 0; trailPosition < actualTrailLength; ++trailPosition) {
      auto pixelPosition = (effectPosition + trailPosition + shift) % pixelLength; // draw tail first
      params.trailPosition = actualTrailLength - 1 - trailPosition;
      params.positionRatio = static_cast<float>(trailPosition + 1) / static_cast<float>(actualTrailLength);
      params.pixelPosition = pixelPosition;
      pixels.set(pixelPosition, shader(pixels.get(pixelPosition), params));
    }
  }
}

}