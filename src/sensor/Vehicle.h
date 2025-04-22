//
// Created by Brandon on 2/24/25.
//

#ifndef RGBLIB_VEHICLE_H
#define RGBLIB_VEHICLE_H

#include <OBD.h>
#include <atomic>
#include <mutex>
#include "Handle.h"
#include "Assertions.h"
#include "time/Clock.h"
#include "Util.h"

namespace rgb {

struct OBDDestroyer {
  auto operator()(COBD& c) const noexcept -> void;
};

class Vehicle {
public:
  template<typename T>
  using TypeRemapper = T(*)(int);

  using mutex = std::recursive_mutex;

  auto update(Duration throttle = Duration::Milliseconds(50)) -> void;
  auto connect() -> bool;
  auto setLowPowerMode(bool value) -> void;

  auto rpm() const -> revs_per_minute;
  auto speed() const -> kph;
  auto coolantTemp() const -> fahrenheit;
  auto fuelLevel() const -> percent;
  auto throttlePosition() const -> percent;
  auto inLowPowerMode() const -> bool;
  auto isConnected() const -> bool;

private:
  Handle<COBD, OBDDestroyer> obdHandle{{}};
  mutable mutex mu{};
  std::atomic<revs_per_minute> mRpm{};
  std::atomic<mph> mSpeed{};
  std::atomic<fahrenheit> mCoolantTemp{};
  std::atomic<percent> mFuelLevel{};
  std::atomic<percent> mThrottlePosition{};
  std::atomic<bool> mConnected{false};
  Timestamp mLastResponse{0};
  Timestamp mLastUpdate{0};
  std::atomic<bool> mLowPowerMode{false};

  auto disconnect() -> void;
//  auto readPID(byte pid, atomic_float& result, Timestamp now) -> void;

  constexpr static auto NoRemapping(int value) -> int { return value; }
  constexpr static auto ToPercent(int value) -> percent { return static_cast<float>(value) / 100.f; }
  constexpr static auto ToFloat(int value) -> float { return static_cast<float>(value); }
  constexpr static auto ToFahrenheit(int value) -> float { return CToF(static_cast<float>(value)); }
  constexpr static auto ToMph(int value) -> float { return KphToMph(static_cast<float>(value)); }

  template<typename T>
  auto readPID(byte pid, std::atomic<T>& result, TypeRemapper<T> remapper = NoRemapping) -> void {
    auto& obd = *obdHandle;
    ASSERT(obd.getState() == OBD_CONNECTED, "OBD not connected");

    int value;
    if (obd.readPID(pid, value)) {
      result = remapper(value);
      mLastResponse = Clock::Now();
    }
    else {
      if (Clock::Now().timeSince(mLastResponse) >= Duration::Seconds(1)) {
        ASSERT(false, "Disconnected");
        disconnect();
      }
    }
  }
};

}

#endif //RGBLIB_VEHICLE_H
