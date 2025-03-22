//
// Created by Brandon on 2/24/25.
//

#include "Vehicle.h"

namespace rgb {

auto OBDDestroyer::operator()(COBD& c) const noexcept -> void {
  c.end();
}

auto Vehicle::connect() -> bool {
  Log.infoLn("Vehicle connect()");
  if (obd.isSet() && obd.get().getState() == OBD_STATES::OBD_CONNECTED) {
    Log.infoLn("Vehicle already connected");
    return true;
  }

  obd.reset({});

  if (!obd.get().begin()) {
    Log.infoLn("Vehicle begin() failed");
    return false;
  }

  if (!obd.get().init()) {
    Log.infoLn("Vehicle init() failed");
    return false;
  }

  Log.infoLn("Vehicle ready");
  digitalWrite(LED_RED, LOW);

  return true;
}

auto Vehicle::disconnect() -> void {
  obd.destroy();
}

auto Vehicle::rpm() -> int {
  if (!obd.isSet() || obd.get().getState() != OBD_CONNECTED) {
    return 0;
  }

  int value;
  if (obd.get().readPID(PID_RPM, value)) {
    return value;
  }
  else {
    return 0;
  }
}

}