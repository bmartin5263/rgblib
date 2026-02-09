//
// Created by Brandon on 7/5/25.
//

#include "RpmColorMode.h"
#include "RpmGauge.h"
#include "rgb/Color.h"

auto RpmColorMode::PARTITIONED() -> const RpmColorMode* {
  return &PartitionedRpmColorMode::Instance();
}

auto RpmColorMode::SINGLE() -> const RpmColorMode* {
  return &SingleRpmColorMode::Instance();
}

auto RpmColorMode::BLENDED() -> const RpmColorMode* {
  return &BlendedRpmColorMode::Instance();
}

auto SingleRpmColorMode::calculateColor(const RpmGaugeCalculations& calcs, const RpmGauge& scene) const -> rgb::Color {
  if (calcs.level < calcs.yellowLevel) {
    if (calcs.rpmLevelAchieved > calcs.redLevel) {
      return scene.redColor;
    }
    else if (calcs.rpmLevelAchieved > calcs.yellowLevel) {
      return scene.yellowColor;
    }
    else {
      return scene.greenColor;
    }
  }
  else if (calcs.level < calcs.redLevel) {
    if (calcs.rpmLevelAchieved > calcs.redLevel) {
      return scene.redColor;
    }
    else {
      return scene.yellowColor;
    }
  }
  else {
    return scene.redColor;
  }
}

auto BlendedRpmColorMode::calculateColor(const RpmGaugeCalculations& calcs, const RpmGauge& scene) const -> rgb::Color {
  auto minRpmToAchieveLevel = (calcs.rpmPerLevel * calcs.level) + calcs.rpmPerLevel;
  if (minRpmToAchieveLevel <= calcs.effectiveYellowLineStart) {
    return scene.greenColor.lerpClamp(scene.yellowColor, static_cast<float>(minRpmToAchieveLevel) / static_cast<float>(calcs.effectiveYellowLineStart));
  }
  else {
    return scene.yellowColor.lerpClamp(scene.redColor, static_cast<float>(minRpmToAchieveLevel) / static_cast<float>(calcs.effectiveRedLineStart));
  }
}

auto PartitionedRpmColorMode::calculateColor(const RpmGaugeCalculations& calcs, const RpmGauge& scene) const -> rgb::Color {
  if (calcs.level < calcs.yellowLevel) {
    return scene.greenColor;
  }
  else if (calcs.level < calcs.redLevel) {
    return scene.yellowColor;
  }
  else {
    return scene.redColor;
  }
}
