//
// Created by Brandon on 4/1/25.
//

#include <FreeRTOS.h>
#include <task.h>
#include "VehicleThread.h"
#include "sensor/Vehicle.h"
#include "Config.h"

namespace rgb {

auto run(void* param) -> void;

auto VehicleThread::start(Vehicle& v) -> void {
  if (!started) {
    xTaskCreatePinnedToCore(
      run,                /* Task function. */
      "Task1",            /* name of task. */
      10000,              /* Stack size of task */
      &v,                 /* parameter of the task */
      1,                  /* priority of the task */
      &taskHandle,        /* Task handle to keep track of created task */
      1);                 /* pin task to core 1 */
    started = true;
  }
}

auto run(void* param) -> void {
  auto* vehicle = (Vehicle*) param;
  vehicle->connect();
  auto lastConnectAttempt = Timestamp::OfMicroseconds(micros());
  while (true) {
    auto now = Timestamp::OfMicroseconds(micros());
    TRACE("Vehicle Loop");
    if (!vehicle->isConnected()) {
      if (now.timeSince(lastConnectAttempt) >= Duration::Seconds(1)) {
        vehicle->connect();
        lastConnectAttempt = now;
      }
    }
//    else {
//      vehicle->update();
//    }
    delay(10);
  }
}

}