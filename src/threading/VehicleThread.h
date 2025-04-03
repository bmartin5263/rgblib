//
// Created by Brandon on 4/1/25.
//

#ifndef RGBLIB_SENSORTHREAD_H
#define RGBLIB_SENSORTHREAD_H

namespace rgb {

class Vehicle;
class VehicleThread {
public:
  static auto Start(Vehicle& vehicle) -> void { Instance().start(vehicle); }

private:
  Vehicle* vehicle;

  auto start(Vehicle& vehicle) -> void;

  static auto Instance() -> VehicleThread& {
    static VehicleThread instance;
    return instance;
  }
};

}


#endif //RGBLIB_SENSORTHREAD_H
