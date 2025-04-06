//
// Created by Brandon on 2/24/25.
//

#include "Vehicle.h"
#include "Config.h"
#include "Clock.h"

namespace rgb {

auto OBDDestroyer::operator()(COBD& c) const noexcept -> void {
  c.end();
}

auto Vehicle::connect() -> bool {
  digitalWrite(LED_BUILTIN, HIGH);
  if ((*obdHandle).getState() == OBD_STATES::OBD_CONNECTED) {
    INFO("Vehicle already connected");
    mConnected = true;
    digitalWrite(LED_BUILTIN, LOW);
    return true;
  }

  INFO("Connecting");

  obdHandle.reset({});
  mConnected = false;

  auto& obd = *obdHandle;

  if (!obd.begin()) {
    ERROR("Vehicle begin() failed");
    digitalWrite(LED_BUILTIN, LOW);
    return false;
  }

  if (!obd.init()) {
    ERROR("Vehicle init() failed");
    digitalWrite(LED_BUILTIN, LOW);
    return false;
  }

  INFO("Vehicle ready");
  digitalWrite(rgb::config::LED_VEHICLE_CONNECTED, LOW);
  digitalWrite(LED_BUILTIN, LOW);
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

  auto now = Clock::Now();
  if (!mConnected && now.TimeSince(mLastCheck) >= Duration::Seconds(5)) {
    mLastCheck = now;
    connect();
//    INFO("Not connected");
    return;
  }

  readPID(PID_RPM, mRpm, Duration::Milliseconds(5), now);
//  readPID(PID_ENGINE_OIL_TEMP, mOilTemp, 1);
//  readPID(PID_COOLANT_TEMP, mCoolantTemp, 1);
  readPID(PID_SPEED, mSpeed, Duration::Milliseconds(5), now);
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

auto Vehicle::readPID(byte pid, atomic_int& result, Duration timeout, Timestamp now) -> void {
  auto& obd = *obdHandle;

  if (obd.getState() != OBD_CONNECTED) {
    return;
  }

  int value;
  if (obd.readPID(pid, value, static_cast<int>(timeout.asMilliseconds()))) {
    result = value;
    mLastResponse = now;
  }
  else {
    if (now.TimeSince(mLastResponse) >= Duration::Seconds(1)) {
      disconnect();
    }
  }
}

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