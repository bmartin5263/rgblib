//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_SENSORMANAGER_H
#define RGBLIB_SENSORMANAGER_H

#include "ISensorManager.h"

#include <array>

using SensorFunction = void (*)();

template <uint N>
class SensorManager : public rgb::ISensorManager {
public:
  SensorManager(
    std::array<SensorFunction, N>& sensorMap
  ):
    sensorMap(sensorMap)
  {}

  auto update() -> void override {
    for (auto& function : sensorMap) {
      function();
    }
  }

private:
  std::array<SensorFunction, N>& sensorMap;
};


#endif //RGBLIB_SENSORMANAGER_H
