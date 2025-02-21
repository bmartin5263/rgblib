//
// Created by Brandon on 1/8/25.
//

#ifndef RGBLIB_CLOCKTIME_H
#define RGBLIB_CLOCKTIME_H

#include "Types.h"

namespace rgb {

struct ClockTime {
  milliseconds millis{};
  frame_time frames{};
};

}


#endif //RGBLIB_CLOCKTIME_H
