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

namespace rgb {

struct OBDDestroyer {
  auto operator()(COBD& c) const noexcept -> void;
};

class Vehicle {
public:
  template<typename T>
  using TypeRemapper = T(*)(T);

  using mutex = std::recursive_mutex;
  using atomic_int = std::atomic_int;
  using atomic_bool = std::atomic_bool;
  using atomic_float = std::atomic<float>;

  auto update() -> void;
  auto connect() -> bool;
  auto setLowPowerMode(bool value) -> void;

  auto rpm() const -> revs_per_minute;
  auto speed() const -> kph;
  auto coolantTemp() const -> fahrenheit;
  auto inLowPowerMode() const -> bool;
  auto isConnected() const -> bool;

private:
  Handle<COBD, OBDDestroyer> obdHandle{{}};
  mutable mutex mu{};
  std::atomic<revs_per_minute> mRpm{};
  std::atomic<mph> mSpeed{};  // mph
  std::atomic<fahrenheit> mCoolantTemp{};
  atomic_bool mConnected{false};
  Timestamp mLastCheck{0};
  Timestamp mLastResponse{0};
  atomic_bool mLowPowerMode{false};

  auto disconnect() -> void;
//  auto readPID(byte pid, atomic_float& result, Timestamp now) -> void;
  auto readPID(const byte pid[], byte count, int result[], int defaultValue = 0) -> bool;

  constexpr static auto DoNothing(float value) -> float {
    return value;
  }

  template<typename T>
  auto readPID(byte pid, std::atomic<T>& result, Timestamp now, TypeRemapper<T> remapper = DoNothing) -> void {
    auto& obd = *obdHandle;
    ASSERT(obd.getState() == OBD_CONNECTED, "OBD not connected");

    int value;
    if (obd.readPID(pid, value)) {
      result = remapper(static_cast<float>(value));
      mLastResponse = now;
    }
    else {
      if (now.TimeSince(mLastResponse) >= Duration::Seconds(1)) {
        disconnect();
      }
    }
  }
};

}

#endif //RGBLIB_VEHICLE_H
