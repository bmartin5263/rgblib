//
// Created by Brandon on 2/24/25.
//

#include "Vehicle.h"
#include "Config.h"
#include "Clock.h"
#include "threading/ThreadPool.h"

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
    digitalWrite(rgb::config::LED_DROPPING_FRAMES, LOW);
    return false;
  }

  if (!obd.init()) {
    ERROR("Vehicle init() failed");
    digitalWrite(rgb::config::LED_DROPPING_FRAMES, LOW);
    return false;
  }

  INFO("Vehicle ready");
  digitalWrite(rgb::config::LED_VEHICLE_CONNECTED, LOW);
  digitalWrite(rgb::config::LED_DROPPING_FRAMES, HIGH);
  mConnected = true;

  return true;
}

auto Vehicle::disconnect() -> void {
  obdHandle.reset({});
  digitalWrite(rgb::config::LED_VEHICLE_CONNECTED, HIGH);
  mConnected = false;
}

auto Vehicle::update() -> void {
//  auto lock = std::unique_lock { mu };

  auto now = Clock::Milli();
  if (!mConnected && (now - lastCheck) >= 5000) {
    lastCheck = now;
    connect();
//    INFO("Not connected");
    return;
  }

  readPID(PID_RPM, mRpm, 1, now);
//  readPID(PID_ENGINE_OIL_TEMP, mOilTemp, 1);
//  readPID(PID_COOLANT_TEMP, mCoolantTemp, 1);
//  readPID(PID_SPEED, mSpeed, 1);
}

auto Vehicle::rpm() const -> revs_per_minute {
  return mRpm;
}

auto Vehicle::oilTemp() const -> celsius {
  return mOilTemp;
}

auto Vehicle::coolantTemp() const -> celsius {
  return mCoolantTemp;
}

auto Vehicle::speed() const-> kph {
  return mSpeed;
}

auto Vehicle::readPID(byte pid, atomic_int& result, milliseconds_t timeout, milliseconds_t now) -> void {
  auto& obd = *obdHandle;

  if (obd.getState() != OBD_CONNECTED) {
    return;
  }

  int value;
  if (obd.readPID(pid, value, (int) timeout)) {
    result = value;
    lastResponse = now;
  }
  else {
    if (now - lastResponse >= 1000) {
      disconnect();
    }
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