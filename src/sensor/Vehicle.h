//
// Created by Brandon on 2/24/25.
//

#ifndef RGBLIB_VEHICLE_H
#define RGBLIB_VEHICLE_H

#include <OBD.h>
#include <atomic>
#include <mutex>
#include <bitset>
#include "Handle.h"
#include "Assertions.h"
#include "Clock.h"
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
  template<class T>
  using atomic = std::atomic<T>;

  static constexpr auto DISCONNECT_TIMEOUT = Duration::Seconds(5);

  auto setTimeout(Duration timeout) -> void;
  auto update() -> void;
  auto connect(pin_num rx = RX, pin_num tx = TX) -> bool;
  auto disconnect() -> void;
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
  atomic<revs_per_minute> mRpm{};
  atomic<kph> mSpeed{};
  atomic<fahrenheit> mCoolantTemp{};
  atomic<percent> mFuelLevel{};
  atomic<percent> mThrottlePosition{};
  atomic<bool> mConnected{false};
  Timestamp mLastResponse{0};
  Timestamp mLastUpdate{0};
  int timeoutMs{25};
  atomic<bool> mLowPowerMode{false};

//  auto readPID(byte pid, atomic_float& result, Timestamp now) -> void;

  constexpr static auto NoRemapping(int value) -> int { return value; }
  constexpr static auto ToUint(int value) -> uint { return static_cast<uint>(value); }
  constexpr static auto ToPercent(int value) -> percent { return static_cast<float>(value) / 100.f; }
  constexpr static auto ToFloat(int value) -> float { return static_cast<float>(value); }
  constexpr static auto ToFahrenheit(int value) -> float { return CToF(static_cast<float>(value)); }
  constexpr static auto ToBitset(int value) -> std::bitset<32> { return std::bitset<32>(value); }

  template<typename T>
  auto readPID(byte pid, std::atomic<T>& result, TypeRemapper<T> remapper = NoRemapping) -> void {
    auto& obd = *obdHandle;
    ASSERT(obd.getState() == OBD_CONNECTED, "OBD not connected");

    int value;
    if (obd.readPID(pid, value, timeoutMs)) {
      result = remapper(value);
      mLastResponse = Clock::Now();
    }
    else {
      if (Clock::Now().timeSince(mLastResponse) >= DISCONNECT_TIMEOUT) {
#if RGB_DEBUG
        FAIL("Disconnected OBD2", Color::MAGENTA(.01f));
#else
        ERROR("Disconnected OBD2");
#endif
        disconnect();
      }
    }
  }
};

}

#endif //RGBLIB_VEHICLE_H
