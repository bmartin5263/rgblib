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
  if (obdHandle->getState() == OBD_STATES::OBD_CONNECTED) {
    INFO("Vehicle already connected");
    mConnected = true;
    return true;
  }

  INFO("Connecting");

  obdHandle.reset({});
  mConnected = false;

  if (!obdHandle->begin()) {
    ERROR("Vehicle begin() failed");
//    ASSERT(false, "false");
    return false;
  }

  if (!obdHandle->init()) {
    ERROR("Vehicle init() failed");
//    ASSERT(false, "false");
    return false;
  }

  INFO("Vehicle ready");
  digitalWrite(rgb::config::LED_VEHICLE_CONNECTED, LOW);
  mConnected = true;
  mLastResponse = Clock::Now();

  return true;
}

auto Vehicle::disconnect() -> void {
  auto lock = std::unique_lock { mu };
  obdHandle.reset({});
  digitalWrite(rgb::config::LED_VEHICLE_CONNECTED, HIGH);
  mConnected = false;
}

auto Vehicle::update(Duration throttle) -> void {
  if (!mConnected) { return; }
  auto lock = std::unique_lock { mu };
//  auto now = Clock::Now();
//
//  if (now.timeSince(mLastUpdate) < throttle) {
//    return;
//  }
//  mLastUpdate = now;

  if (!mConnected) { return; }
  readPID(PID_RPM, mRpm, ToFloat);

  if (!mConnected) { return; }
  readPID(PID_COOLANT_TEMP, mCoolantTemp, ToFahrenheit);

  if (!mConnected) { return; }
  readPID(PID_SPEED, mSpeed, ToMph);

  if (!mConnected) { return; }
  readPID(PID_FUEL_LEVEL, mFuelLevel, ToPercent);

  if (!mConnected) { return; }
  readPID(PID_THROTTLE, mThrottlePosition, ToPercent);

  if (!mConnected) { return; }
  readPID(PID_AMBIENT_TEMP, mThrottlePosition, ToPercent);
}

auto Vehicle::rpm() const -> revs_per_minute {
  return mRpm;
}

auto Vehicle::coolantTemp() const -> fahrenheit {
  return mCoolantTemp;
}

auto Vehicle::fuelLevel() const -> percent {
  return mFuelLevel;
}

auto Vehicle::throttlePosition() const -> percent {
  return mThrottlePosition;
}

auto Vehicle::speed() const-> mph {
  return mSpeed;
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