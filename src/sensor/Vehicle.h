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

  auto readPID(byte pid, int defaultValue = 0) const -> int;
  auto readPID(const byte pid[], byte count, int result[], int defaultValue = 0) const -> bool;

  auto rpm(int defaultValue = 0) const -> revs_per_minute;
  auto speed(int defaultValue = 0) const -> mph;
  auto oilTemp(int defaultValue = 0) const -> fahrenheit;

  auto inLowPowerMode() const -> bool;
  auto setLowPowerMode(bool value) -> void;

private:
  Handle<COBD, OBDDestroyer> obdHandle{{}};
  bool lowPowerMode{false};
};

}

#endif //RGBLIB_VEHICLE_H
