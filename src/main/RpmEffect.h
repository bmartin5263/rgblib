//
// Created by Brandon on 1/31/26.
//

#ifndef RGBLIB_RPMEFFECT_H
#define RGBLIB_RPMEFFECT_H

#include "Effect.h"
#include "rgb/Color.h"
#include "RpmColorMode.h"
#include "RpmLayout.h"
#include "RpmShape.h"
#include "Vehicle.h"

class RpmEffect : public rgb::Effect {
public:
  static constexpr auto RPM_SMOOTHING_FACTOR = 0.03f;
  static constexpr auto RED = rgb::Color::RED();
  static constexpr auto GREEN = rgb::Color::GREEN();

  RpmEffect();

  auto update(rgb::Timestamp now) -> void;
  auto draw(rgb::Timestamp now, rgb::PixelList& pixels) -> void override;

private:
  rgb::Timestamp lastPulseReset{};

public:
  rgb::Color greenColor{rgb::Color::GREEN()};
  rgb::Color yellowColor{rgb::Color::YELLOW()};
  rgb::Color redColor{rgb::Color::RED()};
  rgb::fahrenheit minCoolantLevel{70.f};
  rgb::fahrenheit maxCoolantLevel{150.f};
  const RpmLayout* layout{RpmLayout::TRADITIONAL()};
  const RpmColorMode* colorMode{RpmColorMode::PARTITIONED()};
  RpmShape shape{RpmShape::CIRCLE};
  rgb::revs_per_minute rpm{0};
  uint yellowLineStart{2400};
  uint redLineStart{3200};
  uint limit{3360};
  bool glow{true};
  bool dynamicRedLine{true};
  bool lastFrameWasYellow{false};

  auto getCoolantTemp(rgb::Vehicle& vehicle) -> rgb::fahrenheit;
  auto calculateNextBrightness(const RpmGaugeCalculations&) -> rgb::normal;
};


#endif //RGBLIB_RPMEFFECT_H
