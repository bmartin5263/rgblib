//
// Created by Brandon on 6/8/25.
//

#ifndef RGBLIB_TIMERUTIL_H
#define RGBLIB_TIMERUTIL_H

#include "Func.h"
#include "Types.h"

namespace rgb {

struct TimerResult {
  Duration repeatIn{};
};

using TimerFunction = Consumer<TimerResult&>;

}

#endif //RGBLIB_TIMERUTIL_H
