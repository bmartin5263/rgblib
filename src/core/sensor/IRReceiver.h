//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_IRRECEIVER_SELECTOR_H
#define RGBLIB_IRRECEIVER_SELECTOR_H

#if defined(RGB_ARDUINO_ESP32)
#include "ArduinoIRReceiver.h"
namespace rgb {
using IRReceiver = ArduinoIRReceiver;
}
#elif defined(RGB_NATIVE)
#include "NativeIRReceiver.h"
namespace rgb {
using IRReceiver = NativeIRReceiver;
}
#else
#error Unknown platform for IRReceiver
#endif


#endif //RGBLIB_IRRECEIVER_SELECTOR_H
