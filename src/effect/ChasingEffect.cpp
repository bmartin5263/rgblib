//
// Created by Brandon on 8/17/25.
//

#include "ChasingEffect.h"
#include "Clock.h"

namespace rgb {

auto ChasingEffect::draw(Timestamp now, PixelList& pixels) -> void {
  auto actualTrailLength = trailLength.getUnits(pixels);
  auto pixelLength = pixels.length();

  auto params = ShaderParameters {
    .now = now,
    .duration = progression.duration,
    .trailLength = actualTrailLength,
    .pixelPosition = 0,
    .pixelsLength = pixelLength,
    .trailPosition = 0,
    .positionRatio = 0.0f,
    .brightness = Brightness::GetBrightness(brightness)
  };

  Duration activeDuration; // 2 seconds
  Duration idleDuration; // 1 seconds
  if (progression.durationIsDelay) {
    activeDuration = Duration{progression.duration.value * pixelLength};
    idleDuration = Duration::Seconds(1);
  }
  else {
    activeDuration = progression.duration;
    idleDuration = Duration::Seconds(1);
  }
  auto totalDuration = activeDuration + idleDuration;
  auto idleRatio = idleDuration.ratio<double>(activeDuration);
  auto padding = static_cast<ulong>(pixelLength * idleRatio);
  auto effectiveLength = pixelLength + padding;

  auto headPercent = now.percentOf(totalDuration);
  auto effectPosition = static_cast<ulong>(static_cast<double>(effectiveLength) * headPercent); // round down

  if (buildup) {
    for (auto trailPosition = 0; trailPosition < actualTrailLength; ++trailPosition) {
      if (trailPosition > effectPosition) {
        // Anything after effectPosition is not drawn
        break;
      }
      auto cycle = (effectPosition - trailPosition) / effectiveLength;
      auto pixelPosition = (effectPosition - trailPosition + shift) % effectiveLength; // draw head first

      if (pixelPosition >= pixelLength) {
        // Tail parts may still be visible, don't break
        continue;
      }

      params.trailPosition = trailPosition;
      params.positionRatio = static_cast<float>(actualTrailLength - trailPosition) / static_cast<float>(actualTrailLength);
      params.pixelPosition = pixelPosition;
      params.cycle = cycle;
      pixels.set(pixelPosition, shader(pixels.get(pixelPosition), params));
    }
  }
  else {
    params.cycle = static_cast<uint>(headPercent);
    for (auto trailPosition = 0; trailPosition < actualTrailLength; ++trailPosition) {
      auto pixelPosition = (effectPosition + trailPosition + shift) % effectiveLength; // draw tail first
      params.trailPosition = actualTrailLength - 1 - trailPosition;
      params.positionRatio = static_cast<float>(trailPosition + 1) / static_cast<float>(actualTrailLength);
      params.pixelPosition = pixelPosition;
      pixels.set(pixelPosition, shader(pixels.get(pixelPosition), params));
    }
  }
}

}