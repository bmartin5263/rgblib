//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_LEDSTRIP_SELECTOR_H
#define RGBLIB_LEDSTRIP_SELECTOR_H

#include "Types.h"
#include "RgbwSupport.h"

#define TEMPLATE_DECLARATION template <u16 N, uint PIN, RgbwSupport RGBW_SUPPORT = RgbwSupport::DISABLE>

#if RGB_ARDUINO_ESP32
#include "FastLEDStrip.h"
namespace rgb {
TEMPLATE_DECLARATION
using LEDStrip = FastLEDStrip<N, PIN, RGBW_SUPPORT>;
}
#elif defined(RGB_NATIVE)
#include "NativeLEDStrip.h"
namespace rgb {
TEMPLATE_DECLARATION
using LEDStrip = NativeLEDStrip<N>;
}
#else
#error Unknown platform for LEDStrip
#endif


#endif //RGBLIB_LEDSTRIP_SELECTOR_H
