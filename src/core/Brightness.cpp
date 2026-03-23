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

  const float values[] = { levels.dim, levels.medium, levels.bright, levels.max };
  auto index = static_cast<int>(level) - 1; // -1 is offset to account for BrightnessLevel::OFF

  for (auto i = index; i >= 0; --i) {
    if (values[i] >= 0.0f) {
      return values[i];
    }
  }
  return defaultBrightness;
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

auto Brightness::getIlluminationBrightness() const -> float {
  switch (mLevel) {
    case BrightnessLevel::OFF:
      return 0.0f;
    case BrightnessLevel::DIM:
      return illuminationBrightness.dim;
    case BrightnessLevel::MEDIUM:
      return illuminationBrightness.medium;
    case BrightnessLevel::BRIGHT:
      return illuminationBrightness.bright;
    case BrightnessLevel::MAX:
      return illuminationBrightness.max;
  }
}

auto Brightness::getIndicatorBrightness() const -> float {
  switch (mLevel) {
    case BrightnessLevel::OFF:
      return 0.0f;
    case BrightnessLevel::DIM:
      return indicatorBrightness.dim;
    case BrightnessLevel::MEDIUM:
      return indicatorBrightness.medium;
    case BrightnessLevel::BRIGHT:
      return indicatorBrightness.bright;
    case BrightnessLevel::MAX:
      return indicatorBrightness.max;
  }
}

}