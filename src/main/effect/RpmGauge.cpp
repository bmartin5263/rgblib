//
// Created by Brandon on 1/31/26.
//

#include "RpmGauge.h"
#include "Brightness.h"
#include "Timer.h"
#include "corvette/CorvetteMain.h"

using namespace rgb;

auto calculatePulseBrightness(
  normal brightness,
  normal scale,
  Timestamp now,
  Timestamp lastPulseReset // corrects the time so the beginning of the pulse starts at a low brightness
) -> normal {
  return Lerp(brightness, brightness * scale, Pulse((now - lastPulseReset), Duration::Milliseconds(1000)));
}

auto mapToPixelPosition(uint level, uint ledCount, uint offset = 0) -> u16 {
  return (level + offset) % ledCount;
}

RpmGauge::RpmGauge() = default;

auto RpmGauge::reset(rgb::Timestamp now) -> void {
}


auto RpmGauge::update(Timestamp now) -> void {

}

auto RpmGauge::draw(Timestamp now, PixelList& pixels) -> void {
  auto calcs = RpmGaugeCalculations();
  calcs.now = Clock::Now();
  calcs.coolantPercent = PercentBetween(coolantTempSupplier(), minCoolantLevel, maxCoolantLevel);
  calcs.effectiveYellowLineStart = static_cast<u16>(static_cast<float>(yellowLineStart) * LerpClamp(.6f, 1.0f, calcs.coolantPercent));
  calcs.effectiveRedLineStart = static_cast<u16>(static_cast<float>(redLineStart) * LerpClamp(.8f, 1.0f, calcs.coolantPercent));
  calcs.effectiveOffBrightness = Brightness::GetBrightness({
    .dim = offLowBrightness,
    .bright = offHighBrightness
  });
  calcs.effectiveOnBrightness = Brightness::GetBrightness({
    .dim = onLowBrightness,
    .bright = onHighBrightness
  });

  auto ledCount = pixels.length();
  auto levelCount = shape == RpmShape::LINE ? ledCount : layout->calculateLevels(ledCount);
  calcs.rpmPerLevel = (limit - rpmStart) / levelCount;
  calcs.yellowLevel = (calcs.effectiveYellowLineStart - rpmStart) / calcs.rpmPerLevel;
  calcs.redLevel = (calcs.effectiveRedLineStart - rpmStart) / calcs.rpmPerLevel;

  rpm = smoothRpmSupplier();
  calcs.rpmLevelAchieved = (rpm - min(rpm, rpmStart)) / calcs.rpmPerLevel;

  if (calcs.rpmLevelAchieved == 0 && rpm > 100) {
    ++calcs.rpmLevelAchieved;
  }

  switch (glowCondition) {
    case GlowCondition::YELLOW_LINE:
      calcs.glow = calcs.rpmLevelAchieved > calcs.yellowLevel;
      break;
    case GlowCondition::RED_LINE:
      calcs.glow = calcs.rpmLevelAchieved > calcs.redLevel;
      break;
    default:
      calcs.glow = false;
      break;
  }

  TRACE("rpmPerLevel=%i, yellowLevel=%i, redLevel=%i, achieved=%i, glow=%i", calcs.rpmPerLevel, calcs.yellowLevel, calcs.redLevel, calcs.rpmLevelAchieved, calcs.glow);

  auto offset = shape == RpmShape::LINE ? 0 : layout->calculateOffset(ledCount);

  auto time = now.percentOf(BUILD_UP_TIME);
  auto activeLevel = static_cast<int>(static_cast<float>(levelCount) * time);

  if (rainbowSupplier()) {
    if (!rainbowAchievedAt) {
      rainbowAchievedAt = now;
    }
    auto rainbowBrightness = calcs.effectiveOnBrightness * rainbowBrightnessScale;
    auto fillPercent = (now - rainbowAchievedAt.value()).percentOf(Duration::Milliseconds(300));
    auto fillIndex = pixels.size() * fillPercent;
    auto t = now.percentOfWrapped(RAINBOW_SPEED);
    auto color = Color::HslToRgb(t) * rainbowBrightness;
    pixels.fill(color, levelCount);
    if (fillIndex < pixels.size()) {
      pixels.set(fillIndex, Color::WHITE() * rainbowBrightness * 2);
    }
  }
  else {
    rainbowAchievedAt = std::nullopt;
    for (int level = 0; level < levelCount && level < activeLevel; ++level) {
      calcs.level = level;
      auto color = colorMode->calculateColor(calcs, *this);

      auto brightness = calculateNextBrightness(calcs);

      color *= brightness;
      pixels.set(mapToPixelPosition(level, ledCount, offset), color);
    }
  }

  if (now < BUILD_UP_TIME) {
    pixels.set(activeLevel, Color::WHITE() * calcs.effectiveOnBrightness * 3);
  }
}

auto RpmGauge::calculateNextBrightness(const RpmGaugeCalculations& calcs) -> normal {
  auto effectiveBrightBrightness = calcs.effectiveOnBrightness;
  auto effectiveDimBrightness = calcs.effectiveOffBrightness;
  if (calcs.level >= calcs.rpmLevelAchieved) {
    return effectiveDimBrightness;
  }

  if (calcs.glow) {
    if (!lastFrameWasYellow) {
      lastPulseReset = calcs.now - Duration::Milliseconds(250);
    }
    auto pulseBrightness = calculatePulseBrightness(effectiveBrightBrightness, pulseBrightnessScale, calcs.now, lastPulseReset);
    lastFrameWasYellow = true;
    return pulseBrightness;
  }
  else {
    if (lastFrameWasYellow) {
      auto pulseBrightness = calculatePulseBrightness(effectiveBrightBrightness, pulseBrightnessScale, calcs.now, lastPulseReset);
      if (pulseBrightness <= effectiveBrightBrightness * 1.16f) {
        lastFrameWasYellow = false;
      }
      return pulseBrightness;
    }
    else {
      return effectiveBrightBrightness;
    }
  }
}