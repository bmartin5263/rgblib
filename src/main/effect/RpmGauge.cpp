//
// Created by Brandon on 1/31/26.
//

#include "RpmGauge.h"
#include "Brightness.h"
#include "Timer.h"
#include "lincoln/LincolnTownCar.h"

using namespace rgb;

auto calculatePulseBrightness(
  normal brightness,
  normal scale,
  Timestamp now,
  Timestamp lastPulseReset
) -> normal {
  return Lerp(brightness, brightness * scale, Pulse((now - lastPulseReset), Duration::Milliseconds(1500)));
}

auto mapToPixelPosition(uint level, uint ledCount, uint offset = 0) -> u16 {
  return (level + offset) % ledCount;
}

RpmGauge::RpmGauge() = default;

auto RpmGauge::reset(rgb::Timestamp now) -> void {
}


auto RpmGauge::update(Timestamp now) -> void {
  auto& vehicle = LincolnTownCar::Instance();
  auto calcs = RpmGaugeCalculations();
  calcs.now = Clock::Now();
  calcs.coolantPercent = PercentBetween(getCoolantTemp(vehicle), minCoolantLevel, maxCoolantLevel);
  calcs.effectiveYellowLineStart = static_cast<u16>(static_cast<float>(yellowLineStart) * LerpClamp(.6f, 1.0f, calcs.coolantPercent));
  calcs.effectiveRedLineStart = static_cast<u16>(static_cast<float>(redLineStart) * LerpClamp(.8f, 1.0f, calcs.coolantPercent));
  calcs.effectiveDimBrightness = Brightness::GetBrightness({
    .dim = rgb::ByteToFloat(0),
    .medium = rgb::ByteToFloat(1),
    .bright = rgb::ByteToFloat(4)
  });
  calcs.effectiveBrightBrightness = Brightness::GetBrightness({
    .dim = rgb::ByteToFloat(6),
    .medium = rgb::ByteToFloat(6),
    .bright = rgb::ByteToFloat(40)
  });
}

auto RpmGauge::draw(Timestamp now, PixelList& pixels) -> void {
  auto& vehicle = LincolnTownCar::Instance();
  auto calcs = RpmGaugeCalculations();
  calcs.now = Clock::Now();
  calcs.coolantPercent = PercentBetween(getCoolantTemp(vehicle), minCoolantLevel, maxCoolantLevel);
  calcs.effectiveYellowLineStart = static_cast<u16>(static_cast<float>(yellowLineStart) * LerpClamp(.6f, 1.0f, calcs.coolantPercent));
  calcs.effectiveRedLineStart = static_cast<u16>(static_cast<float>(redLineStart) * LerpClamp(.8f, 1.0f, calcs.coolantPercent));
  calcs.effectiveDimBrightness = Brightness::GetBrightness({
    .dim = rgb::ByteToFloat(0),
    .medium = rgb::ByteToFloat(1),
    .bright = rgb::ByteToFloat(4)
  });
  calcs.effectiveBrightBrightness = Brightness::GetBrightness({
    .dim = rgb::ByteToFloat(6),
    .medium = rgb::ByteToFloat(6),
    .bright = rgb::ByteToFloat(40)
  });


  auto ledCount = pixels.length();
  auto levelCount = shape == RpmShape::LINE ? ledCount : layout->calculateLevels(ledCount);
  calcs.rpmPerLevel = (limit - rpmStart) / levelCount;
  calcs.yellowLevel = (calcs.effectiveYellowLineStart - rpmStart) / calcs.rpmPerLevel;
  calcs.redLevel = (calcs.effectiveRedLineStart - rpmStart) / calcs.rpmPerLevel;

  rpm = vehicle.smoothRpm();
  calcs.rpmLevelAchieved = (rpm - min(rpm, rpmStart)) / calcs.rpmPerLevel;

  if (calcs.rpmLevelAchieved == 0 && rpm > 100) {
    ++calcs.rpmLevelAchieved;
  }
  calcs.glow = calcs.rpmLevelAchieved > calcs.yellowLevel;

  TRACE("rpmPerLevel=%i, yellowLevel=%i, redLevel=%i, achieved=%i, glow=%i", calcs.rpmPerLevel, calcs.yellowLevel, calcs.redLevel, calcs.rpmLevelAchieved, calcs.glow);

  auto offset = shape == RpmShape::LINE ? 0 : layout->calculateOffset(ledCount);

  auto time = now.percentOf(BUILD_UP_TIME);
  auto activeLevel = static_cast<int>(static_cast<float>(levelCount) * time);

  if (rainbow) {
    auto t = Clock::Now().percentOfWrapped(RAINBOW_SPEED);
    auto color = Color::HslToRgb(t) * calcs.effectiveBrightBrightness * 1.5f;
    pixels.fill(color, levelCount);
  }
  else {
    for (int level = 0; level < levelCount && level < activeLevel; ++level) {
      calcs.level = level;
      auto color = colorMode->calculateColor(calcs, *this);

      auto brightness = calculateNextBrightness(calcs);

      color *= brightness;
      pixels.set(mapToPixelPosition(level, ledCount, offset), color);
    }
  }

  if (now < BUILD_UP_TIME) {
    pixels.set(activeLevel, Color::WHITE() * calcs.effectiveBrightBrightness * 2);
  }
}

auto RpmGauge::getCoolantTemp(LincolnTownCar& vehicle) -> fahrenheit {
  if (dynamicRedLine && vehicle.isConnected()) {
    return vehicle.coolantTemp();
  }
  else {
    return maxCoolantLevel;
  }
}

auto RpmGauge::calculateNextBrightness(const RpmGaugeCalculations& calculations) -> rgb::normal {
  if (calculations.level >= calculations.rpmLevelAchieved) {
    return calculations.effectiveDimBrightness;
  }

  if (calculations.glow) {
    if (!lastFrameWasYellow) {
      lastPulseReset = calculations.now - Duration::Milliseconds(500);
    }
    auto brightness = calculatePulseBrightness(calculations.effectiveBrightBrightness, 3.0f, calculations.now, lastPulseReset);
    lastFrameWasYellow = true;
    return brightness;
  }
  else {
    if (lastFrameWasYellow) {
      auto brightness = calculatePulseBrightness(calculations.effectiveBrightBrightness, 3.0f, calculations.now, lastPulseReset);
      if (brightness <= calculations.effectiveBrightBrightness * 1.16f) {
        lastFrameWasYellow = false;
      }
      return brightness;
    }
    else {
      return calculations.effectiveBrightBrightness;
    }
  }
}

auto RpmGauge::startRainbow() -> void {
  rainbow = true;
}

auto RpmGauge::stopRainbow() -> void {
  INFO("stopping rainbow");
  rainbow = false;
}
