//
// Created by Brandon on 4/1/25.
//

#include "VehicleThread.h"
#include "sensor/Vehicle.h"
#include <thread>
#include <iostream>
#include <strstream>

namespace rgb {

auto VehicleThread::start(Vehicle& v) -> void {
  this->vehicle = &v;
  auto t = std::thread([&](){
    while (true) {
      INFO("Vehicle Loop");
      if (!vehicle->isConnected()) {
        vehicle->connect();
      }
//      vehicle->update();
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  });
  t.detach();
}

}