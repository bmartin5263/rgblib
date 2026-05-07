//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_GPIOIMPLEMENTATION_H
#define RGBLIB_GPIOIMPLEMENTATION_H

#if defined(RGB_ARDUINO)
#include "GPIOArduino.h"
namespace rgb::priv { class GPIOImpl : public GPIOArduino {}; };
#elif defined(RGB_ESP32)
#include "GPIOESP32.h"
namespace rgb::priv { class GPIOImpl : public GPIOESP32 {}; };
#endif

#endif //RGBLIB_GPIOIMPLEMENTATION_H
