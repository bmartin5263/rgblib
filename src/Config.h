//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_CONFIG_H
#define RGBLIB_CONFIG_H

#include "pins_arduino.h"
#include "Types.h"

namespace rgb::config {

constexpr auto FPS = 300;
constexpr auto WEB_SERVER_PORT = 80;
constexpr auto TIMERS = 10;
constexpr auto DEBUG_SCREEN_REFRESH_RATE = Duration::Milliseconds(100);
constexpr auto VEHICLE_REFRESH_RATE = Duration::Milliseconds(100);

constexpr auto LED_OTA_CONNECTED = LED_BLUE;
constexpr auto LED_VEHICLE_CONNECTED = LED_GREEN;
constexpr auto LED_DROPPING_FRAMES = LED_RED;

}

#endif //RGBLIB_CONFIG_H
