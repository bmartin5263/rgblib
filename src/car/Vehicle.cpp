//
// Created by Brandon on 2/24/25.
//

#include "Vehicle.h"
#include "Config.h"
#include "Clock.h"
#include "Assertions.h"
#include "Util.h"
#include "Application.h"

namespace rgb {

Vehicle* Vehicle::instance = nullptr;

auto OBDDestroyer::operator()(COBD& c) const noexcept -> void {
  c.end();
}

auto Vehicle::connect(PinNumber rx, PinNumber tx) -> bool {
  auto lock = std::unique_lock { mu };
  if (obdHandle->getState() == OBD_STATES::OBD_CONNECTED) {
    INFO("Vehicle already connected");
    mConnected = true;
    return true;
  }

  // INFO("Connecting");

  obdHandle.reset({});
  mConnected = false;

  if (!obdHandle->begin(rx.to<i8>(), tx.to<i8>())) {
    // ERROR("Vehicle begin() failed");
//    FAIL("Vehicle begin() failed", Color::MAGENTA(.01f));
    return false;
  }

  if (!obdHandle->init()) {
    ERROR("Vehicle init() failed");
//    FAIL("Vehicle init() failed", Color::MAGENTA(.01f));
    return false;
  }

  INFO("Vehicle ready");
  mConnected = true;
  mLastResponse = Clock::Now();

  Application::instance->publishSystemEvent(OBDIIConnected{Clock::Now()});

  return true;
}

auto Vehicle::disconnect() -> void {
  auto lock = std::unique_lock { mu };
  obdHandle.reset({});
  mConnected = false;
  Application::instance->publishSystemEvent(OBDIIDisconnected{Clock::Now()});

  INFO("Vehicle Disconnected");
}

auto Vehicle::update() -> VehicleUpdateCode {
  if (!mConnected) { return VehicleUpdateCode::NONE; }
  auto lock = std::unique_lock { mu };

  if (!mConnected) { return VehicleUpdateCode::NONE; }
  readPID(PID_RPM, mRpm, NoRemapping);

  if (!mConnected) { return VehicleUpdateCode::PARTIAL; }
  readPID(PID_COOLANT_TEMP, mCoolantTemp, ToFahrenheit);

  if (!mConnected) { return VehicleUpdateCode::PARTIAL; }
  readPID(PID_SPEED, mSpeed, NoRemapping);

  if (!mConnected) { return VehicleUpdateCode::PARTIAL; }
  readPID(PID_THROTTLE, mThrottlePosition, ToPercent);

  if (!mConnected) { return VehicleUpdateCode::PARTIAL; }
  readPID(PID_FUEL_LEVEL, mFuelLevel, ToPercent);

  return VehicleUpdateCode::FULL;
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
}

auto Vehicle::setTimeout(Duration timeout) -> void {
  // Convert once to avoid needing to divide every frame
  this->timeoutMs = static_cast<int>(timeout.asMilliseconds());
}

auto Vehicle::Instance() -> Vehicle& {
  return *instance;
}

}