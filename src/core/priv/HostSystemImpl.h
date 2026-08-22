//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_HOSTSYSTEMIMPL_H
#define RGBLIB_HOSTSYSTEMIMPL_H


#if RGB_ARDUINO_ESP32
#include "HostSystemArduino.h"
namespace rgb::priv { class HostSystemImpl : public HostSystemArduino {}; }
#elif defined(RGB_ESP32)
#include "HostSystemESP32.h"
namespace rgb::priv { class HostSystemImpl : public HostSystemESP32 {}; }
#elif defined(RGB_NATIVE)
#include "HostSystemNative.h"
namespace rgb::priv { class HostSystemImpl : public HostSystemNative {}; }
#else
#error Unknown Host System
#endif


#endif //RGBLIB_HOSTSYSTEMIMPL_H
