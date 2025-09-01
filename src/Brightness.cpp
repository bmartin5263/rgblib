//
// Created by Brandon on 7/4/25.
//

#include "Brightness.h"
#include "Assertions.h"

namespace rgb {

auto Brightness::setLevel(BrightnessLevel level) -> void {
  mLevel = level;
}

auto Brightness::decreaseLevel(bool includeOff) -> void {
  switch (mLevel) {
    case BrightnessLevel::OFF:
      break;
    case BrightnessLevel::DIM:
      if (includeOff) {
        mLevel = BrightnessLevel::OFF;
      }
      break;
    case BrightnessLevel::MEDIUM:
      mLevel = BrightnessLevel::DIM;
      break;
    case BrightnessLevel::BRIGHT:
      mLevel = BrightnessLevel::MEDIUM;
      break;
    default:
      ASSERT(false, "Unknown Brightness Level");
  }
}

auto Brightness::increaseLevel() -> void {
  switch (mLevel) {
    case BrightnessLevel::OFF:
      mLevel = BrightnessLevel::DIM;
      break;
    case BrightnessLevel::DIM:
      mLevel = BrightnessLevel::MEDIUM;
      break;
    case BrightnessLevel::MEDIUM:
      mLevel = BrightnessLevel::BRIGHT;
    case BrightnessLevel::BRIGHT:
      break;
    default:
      ASSERT(false, "Unknown Brightness Level");
  }
}

auto Brightness::getBrightness(float onlyBrightness) const -> float {
  if (mLevel == BrightnessLevel::OFF) {
    return 0.0f;
  }
  return onlyBrightness;
}

auto Brightness::getBrightness(float low, float medium) const -> float {
  switch (mLevel) {
    case BrightnessLevel::OFF:
      return 0.0f;
    case BrightnessLevel::DIM:
      return low;
    case BrightnessLevel::MEDIUM:
    case BrightnessLevel::BRIGHT:
      return medium;
    default:
      ASSERT(false, "Unknown Brightness Level");
      return low;
  }
}

auto Brightness::getBrightness(float low, float medium, float high) const -> float {
  switch (mLevel) {
    case BrightnessLevel::OFF:
      return 0.0f;
    case BrightnessLevel::DIM:
      return low;
    case BrightnessLevel::MEDIUM:
      return medium;
    case BrightnessLevel::BRIGHT:
      return high;
    default:
      ASSERT(false, "Unknown Brightness Level");
      return low;
  }
}

}