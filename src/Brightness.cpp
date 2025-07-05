//
// Created by Brandon on 7/4/25.
//

#include "Brightness.h"

namespace rgb {

auto BrightnessConfiguration::MaxBrightness(rgb::normal value) -> BrightnessConfiguration& {
  mMaxBrightness = value;
  return *this;
}

auto BrightnessConfiguration::MinBrightness(rgb::normal value) -> BrightnessConfiguration& {
  mMinBrightness = value;
  return *this;
}

auto BrightnessConfiguration::DefaultBrightness(rgb::normal value) -> BrightnessConfiguration& {
  mDefaultBrightness = value;
  return *this;
}

auto BrightnessConfiguration::Step(rgb::normal value) -> BrightnessConfiguration& {
  mStep = value;
  return *this;
}

auto Brightness::maximumBrightness() -> normal {
  return mConfig.mMaxBrightness;
}

auto Brightness::minimumBrightness() -> normal {
  return mConfig.mMaxBrightness;
}

auto Brightness::defaultBrightness() -> normal {
  return mConfig.mMinBrightness;
}

auto Brightness::step() -> normal {
  return mConfig.mStep;
}

auto Brightness::currentBrightness() -> normal {
  return mCurrentBrightness;
}

auto Brightness::setToMax() -> void {
  mCurrentBrightness = mConfig.mMaxBrightness;
}

auto Brightness::setToMin() -> void {
  mCurrentBrightness = mConfig.mMinBrightness;
}

auto Brightness::setToDefault() -> void {
  mCurrentBrightness = mConfig.mDefaultBrightness;
}

auto Brightness::increase() -> void {
  mCurrentBrightness = std::min(mCurrentBrightness + mConfig.mStep, mConfig.mMaxBrightness);
}

auto Brightness::decrease() -> void {
  mCurrentBrightness = std::max(mCurrentBrightness - mConfig.mStep, mConfig.mMinBrightness);
}

}