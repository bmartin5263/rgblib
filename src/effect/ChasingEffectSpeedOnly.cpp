//
// Created by Brandon on 2/2/26.
//

#include <utility>
#include "ChasingEffectSpeedOnly.h"

namespace rgb {

auto ChasingEffectSpeedOnly::reset(Timestamp now) -> void {
  effectPosition = 0;
  nextMoveTime = now + delay;
}

auto ChasingEffectSpeedOnly::update(Timestamp now) -> void {
  while (now >= nextMoveTime) {
    TRACE("Step now=%llu, nextMoveTime=%llu, diff=%llu", now.asMilliseconds(), nextMoveTime.asMilliseconds(), (now-nextMoveTime).asMilliseconds());
    step();
    nextMoveTime += delay;
  }
}

auto ChasingEffectSpeedOnly::step() -> void {
  effectPosition += 1;
}

auto ChasingEffectSpeedOnly::draw(Timestamp now, PixelList& pixels) -> void {
  auto pixelLength = pixels.length();

  uint actualTrailLength;
  if (std::holds_alternative<normal>(trailLength.variant)) {
    actualTrailLength = static_cast<uint>(static_cast<normal>(pixels.length()) * std::get<normal>(trailLength.variant));
  }
  else {
    actualTrailLength = std::get<uint>(trailLength.variant);
  }

  auto params = ShaderParameters {
    .now = now,
    .delay = delay,
    .trailLength = actualTrailLength,
    .pixelPosition = 0,
    .trailPosition = 0,
    .positionRatio = 0.0f,
  };
  if (buildup) {
    for (auto trailPosition = 0; trailPosition < actualTrailLength; ++trailPosition) {
      if (trailPosition > effectPosition) {
        // Anything before effectPosition is not drawn
        break;
      }
      auto pixelPosition = (effectPosition - trailPosition + shift) % pixelLength; // draw head first
      params.trailPosition = trailPosition;
      params.positionRatio = static_cast<float>(actualTrailLength - trailPosition) / static_cast<float>(actualTrailLength);
      params.pixelPosition = pixelPosition;
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