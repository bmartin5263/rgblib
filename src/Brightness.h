//
// Created by Brandon on 7/4/25.
//

#ifndef RGBLIB_BRIGHTNESS_H
#define RGBLIB_BRIGHTNESS_H

#include "Types.h"

namespace rgb {

enum class BrightnessLevel {
  OFF,
  DIM,
  MEDIUM,
  BRIGHT,
};

class Brightness {
public:
  static auto GetBrightness(float onlyBrightness) -> float { return Instance().getBrightness(onlyBrightness); };
  static auto GetBrightness(float low, float medium) -> float { return Instance().getBrightness(low, medium); };
  static auto GetBrightness(float low, float medium, float high) -> float { return Instance().getBrightness(low, medium, high); };
  static auto GetLevel() -> BrightnessLevel { return Instance().getLevel(); };

  static auto SetLevel(BrightnessLevel level) -> void { Instance().setLevel(level); };
  static auto IncreaseLevel() -> void { Instance().increaseLevel(); };
  static auto DecreaseLevel(bool includeOff = false) -> void { Instance().decreaseLevel(includeOff); };

private:
  BrightnessLevel mLevel{BrightnessLevel::DIM};

  static auto Instance() -> Brightness& {
    static Brightness instance;
    return instance;
  }

  auto getBrightness(float onlyBrightness) const -> float;
  auto getBrightness(float low, float medium) const -> float;
  auto getBrightness(float low, float medium, float high) const -> float;
  auto setLevel(BrightnessLevel level) -> void;
  auto getLevel() const -> BrightnessLevel;
  auto increaseLevel() -> void;
  auto decreaseLevel(bool includeOff) -> void;

};

}


#endif //RGBLIB_BRIGHTNESS_H
