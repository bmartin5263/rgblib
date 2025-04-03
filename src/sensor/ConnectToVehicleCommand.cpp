//
// Created by Brandon on 4/2/25.
//

#include "ConnectToVehicleCommand.h"
#include "sensor/Vehicle.h"
#include "threading/ThreadPool.h"

namespace rgb {

ConnectToVehicleCommand::ConnectToVehicleCommand(rgb::Vehicle* vehicle): vehicle(vehicle) {

}

auto ConnectToVehicleCommand::execute() -> void {
  if (!vehicle->connect()) {
//    ThreadPool::SubmitTask(*this);
  }
}

}