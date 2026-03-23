//
// Created by Brandon on 1/18/26.
//

#ifndef RGBLIB_EFFECTPROGRESSION_H
#define RGBLIB_EFFECTPROGRESSION_H

#include "Types.h"

namespace rgb {

struct EffectProgression {
  Duration duration{}; // either 'delay' or 'activeDuration'
  Duration idleDuration{};
  bool durationIsDelay{};

  static constexpr EffectProgression ConstantTime(Duration duration) {
    return {duration, Duration::Seconds(0), false};
  }

  static constexpr EffectProgression ConstantSpeed(Duration delay) {
    return {delay, Duration::Seconds(0), true};
  }
};


}

#endif //RGBLIB_EFFECTPROGRESSION_H
