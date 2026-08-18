//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_LEDFIBER_SELECTOR_H
#define RGBLIB_LEDFIBER_SELECTOR_H

#include "Types.h"
#include "RgbwSupport.h"

#define TEMPLATE_DECLARATION template <u16 N, uint PIN, RgbwSupport RGBW_SUPPORT = RgbwSupport::DISABLE>

#if defined(RGB_ARDUINO_ESP32)
#include "FastLEDStrip.h"
namespace rgb {
TEMPLATE_DECLARATION
using LEDFiber = FastLEDStrip<N, PIN, RGBW_SUPPORT>;
}
#elif defined(RGB_NATIVE)
#include "NativeLEDStrip.h"
#include "RenderScale.h"
namespace rgb {
TEMPLATE_DECLARATION
using LEDFiber = NativeLEDStrip<N, RenderScale::HALF>;
}
#else
#error Unknown platform for LEDFiber
#endif


#endif //RGBLIB_LEDFIBER_SELECTOR_H
