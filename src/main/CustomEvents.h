//
// Created by Brandon on 1/11/26.
//

#ifndef RGBLIB_CUSTOMEVENTS_H
#define RGBLIB_CUSTOMEVENTS_H

#include "SystemEvents.h"

/**
 * The system detected the car entering highway
 */
struct HighwayModeEntered : public rgb::BaseEvent {};

/**
 * The system detected the car leaving highway
 */
struct HighwayModeExited : public rgb::BaseEvent {};

/**
 * The car accelerated abruptly from a standstill
 */
struct PeelOut : public rgb::BaseEvent {};

#endif //RGBLIB_CUSTOMEVENTS_H
