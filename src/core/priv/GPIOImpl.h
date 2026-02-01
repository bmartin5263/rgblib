//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_GPIOIMPLEMENTATION_H
#define RGBLIB_GPIOIMPLEMENTATION_H

#ifdef RGB_ESP32
#include "GPIOESP32.h"
namespace rgb::priv { class GPIOImpl : public GPIOESP32 {}; };
#elif defined(RGB_ARDUINO)
#include "GPIOArduino.h"
namespace rgb::priv { class GPIOImpl : public GPIOArduino {}; };
#endif

#endif //RGBLIB_GPIOIMPLEMENTATION_H
