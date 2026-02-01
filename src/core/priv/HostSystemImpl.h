//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_HOSTSYSTEMIMPL_H
#define RGBLIB_HOSTSYSTEMIMPL_H


#ifdef RGB_ESP32
#include "HostSystemESP32.h"
namespace rgb::priv { class HostSystemImpl : public HostSystemESP32 {}; }
#elif defined(RGB_ARDUINO)
#include "HostSystemArduino.h"
namespace rgb::priv { class HostSystemImpl : public HostSystemArduino {}; }
#endif


#endif //RGBLIB_HOSTSYSTEMIMPL_H
