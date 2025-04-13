//
// Created by Brandon on 2/24/25.
//

#include "Vehicle.h"
#include "Config.h"
#include "Clock.h"
#include "Assertions.h"
#include "Util.h"

namespace rgb {

auto OBDDestroyer::operator()(COBD& c) const noexcept -> void {
  c.end();
}

auto Vehicle::connect() -> bool {
  auto lock = std::unique_lock { mu };
  if ((*obdHandle).getState() == OBD_STATES::OBD_CONNECTED) {
    INFO("Vehicle already connected");
    mConnected = true;
    return true;
  }

  INFO("Connecting");

  obdHandle.reset({});
  mConnected = false;

  auto& obd = *obdHandle;

  if (!obd.begin()) {
    ERROR("Vehicle begin() failed");
    ASSERT(false, "false");
    return false;
  }

  if (!obd.init()) {
    ERROR("Vehicle init() failed");
    ASSERT(false, "false");
    return false;
  }

  INFO("Vehicle ready");
  digitalWrite(rgb::config::LED_VEHICLE_CONNECTED, LOW);
  mConnected = true;

  return true;
}

auto Vehicle::disconnect() -> void {
  auto lock = std::unique_lock { mu };
  obdHandle.reset({});
  digitalWrite(rgb::config::LED_VEHICLE_CONNECTED, HIGH);
  mConnected = false;
}

auto Vehicle::update() -> void {
  if (!mConnected) {
    return;
  }
  auto lock = std::unique_lock { mu };

  auto now = Clock::Now();
  readPID(PID_RPM, mRpm, now);
  readPID(PID_COOLANT_TEMP, mCoolantTemp, now, CToF);
  readPID(PID_SPEED, mSpeed, now, KphToMph);
}

auto Vehicle::rpm() const -> revs_per_minute {
  return mRpm;
}

auto Vehicle::coolantTemp() const -> fahrenheit {
  return mCoolantTemp;
}

auto Vehicle::speed() const-> mph {
  return mSpeed;
}

//auto Vehicle::readPID(byte pid, atomic_float& result, Timestamp now) -> void {
//  auto& obd = *obdHandle;
//  ASSERT(obd.getState() == OBD_CONNECTED, "OBD not connected");
//
//  int value;
//  if (obd.readPID(pid, value)) {
//    result = static_cast<float>(value);
//    mLastResponse = now;
//  }
//  else {
//    if (now.TimeSince(mLastResponse) >= Duration::Seconds(1)) {
//      ASSERT(false, "Connection lost");
//      disconnect();
//    }
//  }
//}
//
//
//auto Vehicle::readPID2(byte pid, atomic_float& result, Timestamp now) -> void {
//  auto& obd = *obdHandle;
//  ASSERT(obd.getState() == OBD_CONNECTED, "OBD not connected");
//
//  int value;
//  if (obd.readPID(pid, value)) {
//    result = CToF(static_cast<float>(value));
//    mLastResponse = now;
//  }
//  else {
//    if (now.TimeSince(mLastResponse) >= Duration::Seconds(1)) {
//      ASSERT(false, "Connection lost");
//      disconnect();
//    }
//  }
//}

auto Vehicle::readPID(const byte pid[], byte count, int result[], int defaultValue) -> bool {
  auto& obd = obdHandle;
  if (obd->getState() != OBD_CONNECTED) {
    std::fill(result, result + count, defaultValue);
    return false;
  }

  if (obd->readPID(pid, count, result)) {
    return true;
  }
  else {
    std::fill(result, result + count, defaultValue);
    return false;
  }
}

auto Vehicle::inLowPowerMode() const -> bool {
  return mLowPowerMode;
}

auto Vehicle::isConnected() const -> bool {
  return mConnected;
}

auto Vehicle::setLowPowerMode(bool value) -> void {
  auto lock = std::unique_lock { mu };
  mLowPowerMode = value;
  if (mLowPowerMode) {
    digitalWrite(rgb::config::LED_VEHICLE_CONNECTED, HIGH);
  }
  else {
    digitalWrite(rgb::config::LED_VEHICLE_CONNECTED, LOW);
  }
}

}