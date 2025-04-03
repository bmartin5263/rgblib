//
// Created by Brandon on 4/2/25.
//

#ifndef RGBLIB_CONNECTTOVEHICLECOMMAND_H
#define RGBLIB_CONNECTTOVEHICLECOMMAND_H

#include "threading/ThreadCommand.h"

namespace rgb {

class Vehicle;
class ConnectToVehicleCommand : public ThreadCommand {
public:
  ConnectToVehicleCommand(Vehicle* vehicle);
  auto execute() -> void override;

private:
  Vehicle* vehicle;
};

}

#endif //RGBLIB_CONNECTTOVEHICLECOMMAND_H
