//
// Created by Brandon on 4/1/25.
//

#include <FreeRTOS.h>
#include <task.h>
#include "VehicleThread.h"
#include "Vehicle.h"
#include "Config.h"

namespace rgb {

auto run(void* param) -> void;

auto VehicleThread::start(Vehicle& v) -> void {
  this->vehicle = &v;
  if (!started) {
    xTaskCreatePinnedToCore(
      run,                /* Task function. */
      "Task1",            /* name of task. */
      10000,              /* Stack size of task */
      this,                 /* parameter of the task */
      1,                  /* priority of the task */
      &taskHandle,        /* Task handle to keep track of created task */
      1);                 /* pin task to core 1 */
    started = true;
  }
}

auto run(void* param) -> void {
  auto* vehicleThread = (VehicleThread*) param;
  auto* vehicle = vehicleThread->vehicle;
  vehicle->connect();
  auto lastConnectAttempt = Timestamp{};
  auto lastVehicleUpdate = Timestamp{};
  while (true) {
    auto now = Timestamp::OfMicroseconds(micros());
    if (!vehicle->isConnected()) {
      if (now.timeSince(lastConnectAttempt) >= Duration::Seconds(1)) {
        vehicle->connect();
        lastConnectAttempt = now;
      }
    }
    else {
      if (vehicleThread->autoUpdate) {
        if (Clock::Now().timeSince(lastVehicleUpdate) > config::VEHICLE_REFRESH_RATE) {
          vehicle->update();
          lastVehicleUpdate = now;
        }
      }
    }
    delay(10);
  }
}

}