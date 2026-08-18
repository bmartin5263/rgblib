//
// Created by Brandon on 8/9/26.
//

#ifndef RGBLIB_RANDOMIMPLEMENTATION_H
#define RGBLIB_RANDOMIMPLEMENTATION_H

#if defined(RGB_ARDUINO_ESP32) || defined(RGB_ESP32)
#include "RandomESP32.h"
namespace rgb::priv { class RandomImpl : public RandomESP32 {}; };
#else
#include "RandomStd.h"
namespace rgb::priv { class RandomImpl : public RandomStd {}; };
#endif


#endif //RGBLIB_RANDOMIMPLEMENTATION_H
