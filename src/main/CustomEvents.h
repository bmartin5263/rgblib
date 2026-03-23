//
// Created by Brandon on 1/11/26.
//

#ifndef RGBLIB_CUSTOMEVENTS_H
#define RGBLIB_CUSTOMEVENTS_H

#include "SystemEvents.h"

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

#endif //RGBLIB_CUSTOMEVENTS_H
