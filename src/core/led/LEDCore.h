//
// Created by Brandon on 1/24/26.
//

#ifndef RGBLIB_LEDCORE_H
#define RGBLIB_LEDCORE_H

#include "FastLED.h"

namespace rgb {

static auto SetupLEDs() {
  FastLED.setDither(0);
}


static auto DisplayLEDs() {
  FastLED.show();
}

}

#endif //RGBLIB_LEDCORE_H
