//
// Created by Brandon on 5/31/25.
//

#ifndef RGBLIB_EVERY_H
#define RGBLIB_EVERY_H

#include "Types.h"
#include "Func.h"
#include "Clock.h"

namespace rgb {

struct Every {
  Every(Duration duration, Runnable action) :
    duration(duration), action(action), lastExecution()
  {}

  auto update() -> void {
    auto now = Clock::Now();
    if (Clock::Now().timeSince(lastExecution) >= duration) {
      action();
      lastExecution = now;
    }
  }

  auto reset() -> void {
    lastExecution = Clock::Now();
  }

  Duration duration;
  Runnable action;
  Timestamp lastExecution;
};

}


#endif //RGBLIB_EVERY_H
