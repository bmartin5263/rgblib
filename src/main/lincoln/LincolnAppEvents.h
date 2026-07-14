//
// Created by Brandon on 3/30/26.
//

#ifndef RGBLIB_LINCOLNAPPEVENTS_H
#define RGBLIB_LINCOLNAPPEVENTS_H

#include "EventType.h"
#include "UserApplication.h"

struct RainbowModeEntered : rgb::BaseEvent {};
struct RainbowModeExited : rgb::BaseEvent {};
struct CarMoving : rgb::BaseEvent {};
struct CarStopped : rgb::BaseEvent {};

using LincolnAppEvents = rgb::Event<RainbowModeEntered, RainbowModeExited, CarMoving, CarStopped>;
using LincolnApp = rgb::UserApplication<LincolnAppEvents>;

#endif //RGBLIB_LINCOLNAPPEVENTS_H
