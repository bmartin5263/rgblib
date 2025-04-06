//
// Created by Brandon on 2/24/25.
//

#ifndef RGBLIB_VEHICLE_H
#define RGBLIB_VEHICLE_H

#include <OBD.h>
#include <atomic>
#include <shared_mutex>
#include "Handle.h"

namespace rgb {


struct OBDDestroyer {
  auto operator()(COBD& c) const noexcept -> void;
};

class Vehicle {
public:
  using mutex = std::shared_mutex;
  using atomic_int = std::atomic_int;
  using atomic_bool = std::atomic_bool;

  auto update() -> void;
  auto connect() -> bool;
  auto setLowPowerMode(bool value) -> void;

  auto rpm() const -> revs_per_minute;
  auto speed() const -> kph;
  auto oilTemp() const -> celsius;
  auto coolantTemp() const -> celsius;
  auto inLowPowerMode() const -> bool;
  auto isConnected() const -> bool;

private:
  Handle<COBD, OBDDestroyer> obdHandle{{}};
  mutable mutex mu{};
  atomic_int mRpm{};
  atomic_int mSpeed{};
  atomic_int mOilTemp{};
  atomic_int mCoolantTemp{};
  atomic_bool mConnected{false};
  Timestamp mLastCheck{0};
  Timestamp mLastResponse{0};
  atomic_bool mLowPowerMode{false};

  auto disconnect() -> void;
  auto readPID(byte pid, atomic_int& result, Duration timeout, Timestamp now) -> void;
  auto readPID(const byte pid[], byte count, int result[], int defaultValue = 0) -> bool;
};

}

#endif //RGBLIB_VEHICLE_H
