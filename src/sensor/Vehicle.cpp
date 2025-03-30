//
// Created by Brandon on 2/24/25.
//

#include "Vehicle.h"

namespace rgb {

auto OBDDestroyer::operator()(COBD& c) const noexcept -> void {
  c.end();
}

auto Vehicle::connect() -> bool {
//  Log.infoLn("Vehicle connect()");
  if ((*obdHandle).getState() == OBD_STATES::OBD_CONNECTED) {
    TRACE("Vehicle already connected");
    return true;
  }

  obdHandle.reset({});
  auto& obd = *obdHandle;

  if (!obd.begin()) {
    ERROR("Vehicle begin() failed");
    return false;
  }

  if (!obd.init()) {
    ERROR("Vehicle init() failed");
    return false;
  }

  ERROR("Vehicle ready");
  digitalWrite(LED_RED, LOW);

  return true;
}

auto Vehicle::disconnect() -> void {
  obdHandle.reset({});
}

auto Vehicle::rpm(int defaultValue) -> revs_per_minute {
  return readPID(PID_RPM, defaultValue);
}

auto Vehicle::oilTemp(int defaultValue) -> fahrenheit {
  return readPID(PID_ENGINE_OIL_TEMP, defaultValue);
}

auto Vehicle::speed(int defaultValue) -> mph {
  return readPID(PID_SPEED, defaultValue);
}

auto Vehicle::readPID(byte pid, int defaultValue) -> int {
  auto& obd = *obdHandle;

  if (obd.getState() != OBD_CONNECTED) {
    return defaultValue;
  }

  int value;
  if (obd.readPID(pid, value)) {
    return value;
  }
  else {
    return defaultValue;
  }
}

auto Vehicle::readPID(const byte pid[], byte count, int result[], int defaultValue) -> bool {
  auto& obd = *obdHandle;
  if (obd.getState() != OBD_CONNECTED) {
    std::fill(result, result + count, defaultValue);
    return false;
  }

  if (obd.readPID(pid, count, result)) {
    return true;
  }
  else {
    std::fill(result, result + count, defaultValue);
    return false;
  }
}

auto Vehicle::inLowPowerMode() const -> bool {
  return lowPowerMode;
}

auto Vehicle::setLowPowerMode(bool value) -> void {
//  lowPowerMode = value;
//  if (lowPowerMode) {
//    digitalWrite(LED_GREEN, LOW);
//  }
//  else {
//    digitalWrite(LED_GREEN, HIGH);
//  }
}

}