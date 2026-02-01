//
// Created by Brandon on 7/4/25.
//

#include "Brightness.h"
#include "Assertions.h"
#include "Clock.h"

namespace rgb {

auto Brightness::setLevel(BrightnessLevel level) -> void {
  mLastLevel = mLevel;
  mLevel = level;
  mBrightnessSetAt = Clock::Now();
}

auto Brightness::decreaseLevel(bool includeOff) -> void {
  switch (mLevel) {
    case BrightnessLevel::OFF:
      break;
    case BrightnessLevel::DIM:
      if (includeOff) {
        setLevel(BrightnessLevel::OFF);
      }
      break;
    case BrightnessLevel::MEDIUM:
      setLevel(BrightnessLevel::DIM);
      break;
    case BrightnessLevel::BRIGHT:
      setLevel(BrightnessLevel::MEDIUM);
      break;
    case BrightnessLevel::MAX:
      setLevel(BrightnessLevel::BRIGHT);
      break;
  }
}

auto Brightness::increaseLevel() -> void {
  switch (mLevel) {
    case BrightnessLevel::OFF:
      setLevel(BrightnessLevel::DIM);
      break;
    case BrightnessLevel::DIM:
      setLevel(BrightnessLevel::MEDIUM);
      break;
    case BrightnessLevel::MEDIUM:
      setLevel(BrightnessLevel::BRIGHT);
      break;
    case BrightnessLevel::BRIGHT:
      setLevel(BrightnessLevel::MAX);
      break;
    case BrightnessLevel::MAX:
      break;
  }
}

auto Brightness::getBrightness(float onlyBrightness) const -> float {
  if (mLevel == BrightnessLevel::OFF) {
    return 0.0f;
  }
  return onlyBrightness;
}

auto Brightness::getBrightness() const -> float {
  return mDefaultBrightness;
}

auto Brightness::getBrightness(const BrightnessLevels& levels) const -> float {
  auto now = Clock::Now() - mBrightnessSetAt;
  auto previousBrightness = GetBrightness(mLastLevel, mDefaultBrightness, levels);
  auto currentBrightness = GetBrightness(mLevel, mDefaultBrightness, levels);
  return LerpClamp(previousBrightness, currentBrightness, now.as<float>() / mFadeDelay.as<float>());
}

auto Brightness::GetBrightness(BrightnessLevel level, normal defaultBrightness, const BrightnessLevels& levels) -> float {
  if (level == BrightnessLevel::OFF) {
    return 0.0f;
  }

  auto floor = defaultBrightness;

  if (levels.dim >= 0.0f) {
    floor = levels.dim;
  }
  if (level == BrightnessLevel::DIM) {
    return floor;
  }

  if (levels.medium >= 0.0f) {
    floor = levels.medium;
  }
  if (level == BrightnessLevel::MEDIUM) {
    return floor;
  }

  if (levels.bright >= 0.0f) {
    floor = levels.bright;
  }
  if (level == BrightnessLevel::BRIGHT) {
    return floor;
  }

  if (levels.max >= 0.0f) {
    floor = levels.max;
  }
  return floor;
}

auto Brightness::turnOff() -> void {
  if (mLevel != BrightnessLevel::OFF) {
    setLevel(BrightnessLevel::OFF);
  }
}

auto Brightness::turnOn() -> void {
  if (mLevel == BrightnessLevel::OFF) {
    setLevel(mLastLevel);
  }
}

auto Brightness::getLevel() const -> BrightnessLevel {
  return mLevel;
}

}