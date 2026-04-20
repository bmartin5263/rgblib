//
// Created by Brandon on 3/30/26.
//

#ifndef RGBLIB_LINCOLNAPPEVENTS_H
#define RGBLIB_LINCOLNAPPEVENTS_H

#include "EventType.h"
#include "UserApplication.h"

/**
 * Car entered highway
 */
struct HighwayModeEntered : public rgb::BaseEvent {};

/**
 * Car left highway
 */
struct HighwayModeExited : public rgb::BaseEvent {};

/**
 * Car floored it from a standstill
 */
struct PeelOut : public rgb::BaseEvent {};

struct RainbowModeEntered : public rgb::BaseEvent {};

struct RainbowModeExited : public rgb::BaseEvent {};

using LincolnAppEvents = rgb::Event<HighwayModeEntered, HighwayModeExited, PeelOut, RainbowModeEntered, RainbowModeExited>;
using LincolnApp = rgb::UserApplication<LincolnAppEvents>;

#endif //RGBLIB_LINCOLNAPPEVENTS_H
