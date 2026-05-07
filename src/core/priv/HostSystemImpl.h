//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_HOSTSYSTEMIMPL_H
#define RGBLIB_HOSTSYSTEMIMPL_H


#if defined(RGB_ARDUINO)
#include "HostSystemArduino.h"
namespace rgb::priv { class HostSystemImpl : public HostSystemArduino {}; }
#elif defined(RGB_ESP32)
#include "HostSystemESP32.h"
namespace rgb::priv { class HostSystemImpl : public HostSystemESP32 {}; }
#else
#error Unknown Host System
#endif


#endif //RGBLIB_HOSTSYSTEMIMPL_H
