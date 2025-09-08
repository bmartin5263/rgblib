//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_CONFIG_H
#define RGBLIB_CONFIG_H

#include "pins_arduino.h"
#include "Types.h"

namespace rgb::config {

constexpr auto FPS = 300;
constexpr auto LED_OTA_CONNECTED = LED_BLUE;
constexpr auto LED_VEHICLE_CONNECTED = LED_GREEN;
constexpr auto LED_DROPPING_FRAMES = LED_RED;

}

#endif //RGBLIB_CONFIG_H
