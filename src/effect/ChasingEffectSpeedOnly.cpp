//
// Created by Brandon on 2/2/26.
//

#include <utility>
#include "ChasingEffectSpeedOnly.h"

namespace rgb {

namespace {

// Wraps a signed index into [0, length)
constexpr auto wrapIndex(i64 value, uint length) -> uint {
  auto wrapped = value % static_cast<i64>(length);
  if (wrapped < 0) {
    wrapped += static_cast<i64>(length);
  }
  return static_cast<uint>(wrapped);
}

}

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
  auto totalLength = pixels.length();
  auto pixelLength = totalLength - trim.getUnits(pixels);
  auto actualTrailLength = trailLength.getUnitsSized(pixelLength);

  auto params = ShaderParameters {
    .now = now,
    .delay = delay,
    .trailLength = actualTrailLength,
    .pixelPosition = 0,
    .trailPosition = 0,
    .positionRatio = 0.0f,
  };

  // Maps a position within the untrimmed window to a pixel index, flipping the
  // window to the far end of the buffer when reversed so trim always shaves off
  // the pixels farthest from the effect's direction of travel
  auto toPixelPosition = [totalLength, pixelLength, reversed = reversed](i64 windowPosition) {
    auto localPosition = wrapIndex(windowPosition, pixelLength);
    return reversed ? (totalLength - 1 - localPosition) : localPosition;
  };

  if (buildup) {
    for (auto trailPosition = 0; trailPosition < actualTrailLength; ++trailPosition) {
      if (trailPosition > effectPosition) {
        // Anything before effectPosition is not drawn
        break;
      }
      auto pixelPosition = toPixelPosition(static_cast<i64>(effectPosition) - trailPosition + shift); // draw head first
      params.trailPosition = trailPosition;
      params.positionRatio = static_cast<float>(actualTrailLength - trailPosition) / static_cast<float>(actualTrailLength);
      params.pixelPosition = pixelPosition;
      pixels.set(pixelPosition, shader(pixels.get(pixelPosition), params));
    }
  }
  else {
    for (auto trailPosition = 0; trailPosition < actualTrailLength; ++trailPosition) {
      auto pixelPosition = toPixelPosition(static_cast<i64>(effectPosition) + trailPosition + shift); // draw tail first
      params.trailPosition = actualTrailLength - 1 - trailPosition;
      params.positionRatio = static_cast<float>(trailPosition + 1) / static_cast<float>(actualTrailLength);
      params.pixelPosition = pixelPosition;
      pixels.set(pixelPosition, shader(pixels.get(pixelPosition), params));
    }
  }
}

}