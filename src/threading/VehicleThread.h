//
// Created by Brandon on 4/1/25.
//

#ifndef RGBLIB_SENSORTHREAD_H
#define RGBLIB_SENSORTHREAD_H

#include <task.h>

namespace rgb {

class Vehicle;
class VehicleThread {
public:
  static auto Start(Vehicle& vehicle) -> void { Instance().start(vehicle); }

  Vehicle* vehicle;
  bool autoUpdate{false};

  static auto Instance() -> VehicleThread& {
    static VehicleThread instance;
    return instance;
  }

private:
  TaskHandle_t taskHandle{};
  bool started{false};

  auto start(Vehicle& vehicle) -> void;
};

}


#endif //RGBLIB_SENSORTHREAD_H
