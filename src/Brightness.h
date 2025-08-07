//
// Created by Brandon on 7/4/25.
//

#ifndef RGBLIB_BRIGHTNESS_H
#define RGBLIB_BRIGHTNESS_H

#include "Types.h"

namespace rgb {

class Brightness;
class BrightnessConfiguration {
public:
  auto MinBrightness(normal value) -> BrightnessConfiguration&;
  auto MaxBrightness(normal value) -> BrightnessConfiguration&;
  auto DefaultBrightness(normal value) -> BrightnessConfiguration&;
  auto Step(normal value) -> BrightnessConfiguration&;

private:
  friend class Brightness;

  normal mMinBrightness{0.0f};
  normal mMaxBrightness{1.0f};
  normal mDefaultBrightness{.05f};
  normal mStep{.01f};
};

class Brightness {
public:
  static auto Configure() -> BrightnessConfiguration& { return Instance().mConfig; };
  static auto SetToMax() -> void { Instance().setToMax(); }
  static auto SetToMin() -> void { Instance().setToMin(); }
  static auto SetToDefault() -> void { Instance().setToDefault(); }
  static auto Increase() -> void { Instance().increase(); }
  static auto Decrease() -> void { Instance().decrease(); }

  static auto Current() -> normal { return Instance().currentBrightness(); };
  static auto Minimum() -> normal { return Instance().minimumBrightness(); };
  static auto Maximum() -> normal { return Instance().maximumBrightness(); };
  static auto Default() -> normal { return Instance().defaultBrightness(); };
  static auto Step() -> normal { return Instance().step(); };

private:
  BrightnessConfiguration mConfig{};
  normal mCurrentBrightness{mConfig.mDefaultBrightness};

  static auto Instance() -> Brightness& {
    static Brightness instance;
    return instance;
  }

  auto currentBrightness() const -> normal;
  auto minimumBrightness() const -> normal;
  auto maximumBrightness() const -> normal;
  auto defaultBrightness() const -> normal;
  auto step() const -> normal;
  auto setToMax() -> void;
  auto setToMin() -> void;
  auto setToDefault() -> void;
  auto increase() -> void;
  auto decrease() -> void;

};

}


#endif //RGBLIB_BRIGHTNESS_H
