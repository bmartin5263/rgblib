//
// Created by Brandon on 2/24/25.
//

#ifndef RGBLIB_VEHICLE_H
#define RGBLIB_VEHICLE_H

#include <OBD.h>
#include "Handle.h"

namespace rgb {

struct OBDDestroyer {
  auto operator()(COBD& c) const noexcept -> void;
};

class Vehicle {
public:
  auto connect() -> bool;
  auto disconnect() -> void;

  auto rpm() -> int;

private:
  Handle<COBD, OBDDestroyer> obd{{}};
};

}

#endif //RGBLIB_VEHICLE_H
