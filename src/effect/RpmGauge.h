//
// Created by Brandon on 1/31/26.
//

#ifndef RGBLIB_RPMGAUGE_H
#define RGBLIB_RPMGAUGE_H

#include "Effect.h"
#include "RgbColor.h"
#include "RpmColorMode.h"
#include "RpmLayout.h"
#include "RpmShape.h"
#include "Flag.h"

enum class GlowCondition {
  NONE, YELLOW_LINE, RED_LINE
};

class Vehicle;
class RpmGauge : public rgb::Effect {
public:
  static constexpr auto RPM_SMOOTHING_FACTOR = 0.03f;
  static constexpr auto RED = rgb::Color::RED();
  static constexpr auto GREEN = rgb::Color::GREEN();
  static constexpr auto BUILD_UP_TIME = rgb::Duration::Milliseconds(200);
  static constexpr auto RAINBOW_SPEED = rgb::Duration::Seconds(1);

  RpmGauge();

  auto reset(rgb::Timestamp now) -> void override;
  auto update(rgb::Timestamp now) -> void override;
  auto draw(rgb::Timestamp now, rgb::PixelList& pixels) -> void override;

private:
  rgb::Timestamp lastPulseReset{};

public:
  Supplier<rgb::fahrenheit> coolantTempSupplier{[](){ return 200.f; }};
  Supplier<rgb::revs_per_minute> smoothRpmSupplier{[](){ return 0; }};
  Supplier<bool> rainbowSupplier{[](){ return false; }};
  rgb::Color greenColor{rgb::Color::GREEN()};
  rgb::Color yellowColor{rgb::Color::YELLOW()};
  rgb::Color redColor{rgb::Color::RED()};
  rgb::flag rainbowAchievedAt{};
  rgb::fahrenheit minCoolantLevel{70.f};
  rgb::fahrenheit maxCoolantLevel{150.f};
  float offLowBrightness{rgb::ByteToFloat(1)};
  float onLowBrightness{rgb::ByteToFloat(4)};
  float offHighBrightness{rgb::ByteToFloat(7)};
  float onHighBrightness{rgb::ByteToFloat(40)};
  float pulseBrightnessScale{3.0f};
  float rainbowBrightnessScale{1.5f};
  const RpmLayout* layout{RpmLayout::TRADITIONAL()};
  const RpmColorMode* colorMode{RpmColorMode::SINGLE()};
  RpmShape shape{RpmShape::CIRCLE};
  rgb::revs_per_minute rpm{0};
  rgb::revs_per_minute yellowLineStart{2350};
  rgb::revs_per_minute redLineStart{2700};
  rgb::revs_per_minute limit{2800};
  rgb::revs_per_minute rpmStart{900};
  GlowCondition glowCondition{GlowCondition::YELLOW_LINE};
  bool glow{true};
  bool dynamicRedLine{true};
  bool lastFrameWasYellow{false};

  auto calculateNextBrightness(const RpmGaugeCalculations&) -> rgb::normal;
};


#endif //RGBLIB_RPMGAUGE_H
