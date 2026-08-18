//
// Created by Brandon on 1/24/26.
//

#ifndef RGBLIB_LEDCORE_H
#define RGBLIB_LEDCORE_H

#if defined(RGB_ARDUINO_ESP32)
#include "FastLED.h"

namespace rgb {

static auto SetupLEDs() {
  FastLED.setDither(0);
}

static auto DisplayLEDs() {
  FastLED.show();
}

}
#elif defined(RGB_NATIVE)
#include "NativeDisplay.h"

namespace rgb {

static auto SetupLEDs() {
  NativeDisplay::Setup();
}

static auto DisplayLEDs() {
  NativeDisplay::Present();
}

}
#else
#error Unknown platform for LEDCore
#endif

#endif //RGBLIB_LEDCORE_H
