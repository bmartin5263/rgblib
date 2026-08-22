//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_CLOCKIMPLEMENTATION_H
#define RGBLIB_CLOCKIMPLEMENTATION_H

#if RGB_ARDUINO_ESP32
#include "ClockArduino.h"
namespace rgb::priv { class ClockImpl : public ClockArduino {}; }
#elif defined(RGB_NATIVE)
#include "ClockNative.h"
namespace rgb::priv { class ClockImpl : public ClockNative {}; }
#else
#error Unknown platform for Clock
#endif

#endif //RGBLIB_CLOCKIMPLEMENTATION_H
