//
// Created by Brandon on 3/18/25.
//

#ifndef RGBLIB_GRID_H
#define RGBLIB_GRID_H

#include "Types.h"
#include "led/LEDCircuit.h"
#include "sensor/PushButton.h"
#include "sensor/Vehicle.h"

namespace rgb {

struct Grid {
  LEDCircuit<12> ring{D2};
  PushButton next{D5};
  PushButton prev{D6};
  Vehicle vehicle{/*D0, D1*/};
};

}

#endif //RGBLIB_GRID_H
