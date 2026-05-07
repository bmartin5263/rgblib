//
// Created by Brandon on 7/4/25.
//

#ifndef RGBLIB_BRIGHTNESS_H
#define RGBLIB_BRIGHTNESS_H

#include "Types.h"
#include "Util.h"

namespace rgb {

enum class BrightnessLevel {
  OFF,
  DIM, // LOW is a macro name in Arduino
  MEDIUM,
  BRIGHT, // HIGH is a macro name in Arduino
  MAX,
};

struct BrightnessLevels {
  float dim{-1.0f};
  float medium{-1.0f};
  float bright{-1.0f};
  float max{-1.0f};

  static constexpr auto DefaultIndicatorBrightness() -> BrightnessLevels {
    using rgb::ByteToFloat;
    return { .dim = ByteToFloat(1), .medium = ByteToFloat(6), .bright = ByteToFloat(20), .max = ByteToFloat(40) };
  }

  static constexpr auto DefaultIlluminationBrightness() -> BrightnessLevels {
    using rgb::ByteToFloat;
    return { .dim = .4f, .medium = .6f, .bright = .8f, .max = 1.0f };
  }
};

class Brightness {
public:
  static auto GetBrightness(const BrightnessLevels& levels) -> float { return Instance().getBrightness(levels); };
  static auto GetLevel() -> BrightnessLevel { return Instance().getLevel(); };

  static auto TurnOff() -> void { Instance().turnOff(); };
  static auto TurnOn() -> void { Instance().turnOn(); };
  static auto SetLevel(BrightnessLevel level) -> void { Instance().setLevel(level); };
  static auto IncreaseLevel() -> void { Instance().increaseLevel(); };
  static auto DecreaseLevel(bool includeOff = false) -> void { Instance().decreaseLevel(includeOff); };

private:
  BrightnessLevel mLevel{BrightnessLevel::MEDIUM};
  BrightnessLevel mLastLevel{mLevel};
  Timestamp mBrightnessSetAt{Timestamp::Zero()};
  Duration mFadeDelay{Duration::Milliseconds(500)};
  normal mDefaultBrightness{1.0f};

  static auto Instance() -> Brightness& {
    static Brightness instance;
    return instance;
  }

  auto getBrightness(const BrightnessLevels& levels) const -> float;
  auto turnOff() -> void;
  auto turnOn() -> void;
  auto setLevel(BrightnessLevel level) -> void;
  auto getLevel() const -> BrightnessLevel;
  auto increaseLevel() -> void;
  auto decreaseLevel(bool includeOff) -> void;

  static auto GetBrightness(BrightnessLevel level, normal defaultLevel, const BrightnessLevels& levels) -> float;
};

}


#endif //RGBLIB_BRIGHTNESS_H
