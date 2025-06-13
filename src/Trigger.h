//
// Created by Brandon on 6/12/25.
//

#ifndef RGBLIB_TRIGGER_H
#define RGBLIB_TRIGGER_H

#include "Types.h"
#include "Func.h"
#include "Clock.h"

namespace rgb {

struct Trigger {
  Trigger(Predicate condition, Duration repeatDelay = Duration::Max()) :
    condition(condition), repeatDelay(repeatDelay), lastFiredAt(), fired(false)
  {}

  auto test() -> bool {
    auto isConditionTrue = condition();
    if (isConditionTrue) {
      auto now = Clock::Now();
      if (!fired || now.timeSince(lastFiredAt) >= repeatDelay) {
        fired = true;
        lastFiredAt = now;
        return true;
      }
      else {
        return false;
      }
    }
    else {
      fired = false;
      return false;
    }
  }

  Predicate condition;
  Duration repeatDelay;
  Timestamp lastFiredAt;
  bool fired;
};

}

#endif //RGBLIB_TRIGGER_H
