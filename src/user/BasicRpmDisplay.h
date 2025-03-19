//
// Created by Brandon on 3/17/25.
//

#ifndef RGBLIB_BASICRPMDISPLAY_H
#define RGBLIB_BASICRPMDISPLAY_H

#include "Scene.h"
#include "led/LEDCircuit.h"
#include "sensor/Vehicle.h"

namespace rgb {

class BasicRpmDisplay : public Scene {
public:
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;

private:
  LEDCircuit<16> circuit{D2};
  Vehicle vehicle{};
  int rpm{};

};

}

#endif //RGBLIB_BASICRPMDISPLAY_H
