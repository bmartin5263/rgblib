//
// Created by Brandon on 1/31/26.
//

#include "RpmEffect.h"
#include "Brightness.h"
#include "Brightness.h"

using namespace rgb;

auto calculatePulseBrightness(
  normal brightness,
  normal scale,
  Timestamp now,
  Timestamp lastPulseReset
) -> normal {
  return Lerp(brightness, brightness * scale, Pulse((now - lastPulseReset).asSeconds(), 1.5f));
}

auto mapToPixelPosition(uint level, uint ledCount, uint offset = 0) -> u16 {
  return (level + offset) % ledCount;
}

RpmEffect::RpmEffect() = default;

auto RpmEffect::update(Timestamp now) -> void {

}

auto RpmEffect::draw(Timestamp now, PixelList& pixels) -> void {
  auto& vehicle = Vehicle::Instance();
  auto calcs = RpmGaugeCalculations();
  calcs.now = Clock::Now();
  calcs.coolantPercent = PercentBetween(getCoolantTemp(vehicle), minCoolantLevel, maxCoolantLevel);
  calcs.effectiveYellowLineStart = static_cast<u16>(static_cast<float>(yellowLineStart) * LerpClamp(.6f, 1.0f, calcs.coolantPercent));
  calcs.effectiveRedLineStart = static_cast<u16>(static_cast<float>(redLineStart) * LerpClamp(.8f, 1.0f, calcs.coolantPercent));
  calcs.effectiveDimBrightness = Brightness::GetBrightness({
    .dim = rgb::ByteToFloat(1),
    .medium = rgb::ByteToFloat(2),
    .bright = rgb::ByteToFloat(4)
  });
  calcs.effectiveDimBrightness = Brightness::GetBrightness({
    .dim = rgb::ByteToFloat(6),
    .medium = rgb::ByteToFloat(20),
    .bright = rgb::ByteToFloat(40)
  });

  auto ledCount = pixels.length();
  auto levelCount = shape == RpmShape::LINE ? ledCount : layout->calculateLevels(ledCount);
  calcs.rpmPerLevel = limit / levelCount;
  calcs.yellowLevel = calcs.effectiveYellowLineStart / calcs.rpmPerLevel;
  calcs.redLevel = calcs.effectiveRedLineStart / calcs.rpmPerLevel;

  RunningAverage(rpm, vehicle.rpm(), RPM_SMOOTHING_FACTOR);

  calcs.rpmLevelAchieved = static_cast<uint>(rpm / calcs.rpmPerLevel);
  if (calcs.rpmLevelAchieved == 0 && rpm > 100) {
    ++calcs.rpmLevelAchieved;
  }
  calcs.glow = calcs.rpmLevelAchieved > calcs.yellowLevel;

  auto offset = shape == RpmShape::LINE ? 0 : layout->calculateOffset(ledCount);
  for (int level = 0; level < levelCount; ++level) {
    calcs.level = level;
    auto color = colorMode->calculateColor(calcs, *this);

    auto brightness = calculateNextBrightness(calcs);

    color *= brightness;
    pixels.set(mapToPixelPosition(level, ledCount, offset), color);
  }
}

auto RpmEffect::getCoolantTemp(Vehicle& vehicle) -> fahrenheit {
  if (dynamicRedLine && vehicle.isConnected()) {
    return vehicle.coolantTemp();
  }
  else {
    return maxCoolantLevel;
  }
}

auto RpmEffect::calculateNextBrightness(const RpmGaugeCalculations& calculations) -> rgb::normal {
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
