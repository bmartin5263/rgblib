//
// Created by Brandon on 5/31/25.
//

#ifndef RGBLIB_EVERY_H
#define RGBLIB_EVERY_H

#include "Types.h"
#include "Func.h"
#include "Clock.h"

namespace rgb {

auto every(Duration duration, Timestamp& lastExecutedAt) -> bool {
  auto now = Clock::Now();
  if (now.timeSince(lastExecutedAt) >= duration) {
    lastExecutedAt = now;
    return true;
  }
  return false;
}

}


#endif //RGBLIB_EVERY_H
