//
// Created by Brandon on 1/31/26.
//

#ifndef RGBLIB_RPMGAUGE_H
#define RGBLIB_RPMGAUGE_H

#include "Effect.h"
#include "rgb/Color.h"
#include "RpmColorMode.h"
#include "RpmLayout.h"
#include "RpmShape.h"
#include "lincoln/LincolnTownCar.h"

class RpmGauge : public rgb::Effect {
public:
  static constexpr auto RPM_SMOOTHING_FACTOR = 0.03f;
  static constexpr auto RED = rgb::Color::RED();
  static constexpr auto GREEN = rgb::Color::GREEN();

  RpmGauge();

  auto reset(rgb::Timestamp now) -> void override;
  auto update(rgb::Timestamp now) -> void override;
  auto draw(rgb::Timestamp now, rgb::PixelList& pixels) -> void override;

  auto startRainbow() -> void;
  auto stopRainbow() -> void;

private:
  rgb::Timestamp lastPulseReset{};

public:
  rgb::Color greenColor{rgb::Color::GREEN()};
  rgb::Color yellowColor{rgb::Color::YELLOW()};
  rgb::Color redColor{rgb::Color::RED()};
  rgb::fahrenheit minCoolantLevel{70.f};
  rgb::fahrenheit maxCoolantLevel{150.f};
  const RpmLayout* layout{RpmLayout::TRADITIONAL()};
  const RpmColorMode* colorMode{RpmColorMode::SINGLE()};
  RpmShape shape{RpmShape::CIRCLE};
  rgb::revs_per_minute rpm{0};
  rgb::revs_per_minute yellowLineStart{2350};
  rgb::revs_per_minute redLineStart{2700};
  rgb::revs_per_minute limit{2800};
  rgb::revs_per_minute rpmStart{900};
  bool glow{true};
  bool dynamicRedLine{true};
  bool lastFrameWasYellow{false};
  bool rainbow{false};

  auto getCoolantTemp(LincolnTownCar& vehicle) -> rgb::fahrenheit;
  auto calculateNextBrightness(const RpmGaugeCalculations&) -> rgb::normal;
};


#endif //RGBLIB_RPMGAUGE_H
