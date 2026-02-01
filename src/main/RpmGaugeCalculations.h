//
// Created by Brandon on 7/5/25.
//

#ifndef LINCOLNLIGHTS_RPMGAUGECALCULATIONS_H
#define LINCOLNLIGHTS_RPMGAUGECALCULATIONS_H

#include "Types.h"

struct RpmGaugeCalculations {
  rgb::Timestamp now{};
  rgb::normal coolantPercent{};
  rgb::normal effectiveBrightBrightness{};
  rgb::normal effectiveDimBrightness{};
  rgb::u16 effectiveYellowLineStart{};
  rgb::u16 rpmPerLevel{};
  rgb::u16 effectiveRedLineStart{};
  rgb::u16 rpmLevelAchieved{};
  rgb::u16 yellowLevel{};
  rgb::u16 redLevel{};
  rgb::u16 level{};
  bool glow{};
};

#endif //LINCOLNLIGHTS_RPMGAUGECALCULATIONS_H
