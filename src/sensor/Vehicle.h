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

  auto readPID(byte pid, int defaultValue = 0) -> int;
  auto readPID(const byte pid[], byte count, int result[], int defaultValue = 0) -> bool;

  auto rpm(revs_per_minute defaultValue = 0) -> revs_per_minute;
  auto speed(kph defaultValue = 0) -> kph;
  auto oilTemp(celsius defaultValue = 0) -> celsius;
  auto coolantTemp(celsius defaultValue = 0) -> celsius;

  auto inLowPowerMode() const -> bool;
  auto setLowPowerMode(bool value) -> void;

private:
  Handle<COBD, OBDDestroyer> obdHandle{{}};
  bool lowPowerMode{false};
};

}

#endif //RGBLIB_VEHICLE_H
