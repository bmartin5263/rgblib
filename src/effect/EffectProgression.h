//
// Created by Brandon on 1/18/26.
//

#ifndef RGBLIB_EFFECTPROGRESSION_H
#define RGBLIB_EFFECTPROGRESSION_H

#include "Types.h"

namespace rgb {

struct EffectProgression {
  Duration duration{};
  bool isDelay{};

  static constexpr EffectProgression ConstantTime(Duration duration) {
    return {duration, false};
  }

  static constexpr EffectProgression ConstantSpeed(Duration delay) {
    return {delay, true};
  }
};


}

#endif //RGBLIB_EFFECTPROGRESSION_H
