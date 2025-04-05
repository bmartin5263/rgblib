//
// Created by Brandon on 1/8/25.
//

#ifndef RGBLIB_CLOCKTIME_H
#define RGBLIB_CLOCKTIME_H

#include "Types.h"

namespace rgb {

struct ClockTime {
  microseconds_t micro{};
  milliseconds_t milli{};
  frames_t frame{};
};

}


#endif //RGBLIB_CLOCKTIME_H
