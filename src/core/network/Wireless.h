//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_WIRELESS_H
#define RGBLIB_WIRELESS_H

#if defined(RGB_ARDUINO_ESP32)

#include <esp_wifi_types.h>
#include <WiFiType.h>
#include "TimerHandle.h"
#include "Types.h"

namespace rgb {

static constexpr auto StrLength(const char* string) -> size_t {
  size_t length = 0;
  if (string == nullptr) {
    return length;
  }
  while (*string++ != '\0') {
    ++length;
  }
  return length;
}

class Wifi {
  using WifiStatus = wl_status_t;

#if defined(RGB_WIFI_SSID)
  static constexpr const char* SSID = RGB_WIFI_SSID;
#else
  static constexpr const char* SSID = "";
#endif
#if defined(RGB_WIFI_PASSWORD)
  static constexpr const char* PASSWORD = RGB_WIFI_PASSWORD;
#else
  static constexpr const char* PASSWORD = "";
#endif
static constexpr auto ENABLED = StrLength(SSID) > 0;

public:
  static constexpr auto WIFI_RECONNECT_TIMEOUT = Duration::Seconds(5);

  constexpr static auto Enabled() -> bool {
    return ENABLED;
  }

  static auto SetMode(wifi_mode_t mode) -> void;
  static auto Start() -> int { return Instance().start(); }
  static auto Update() -> void { Instance().update(); }
  static auto GetStatus() -> int { return Instance().getStatus(); }
  static auto GetAddress() -> IPAddress { return Instance().getAddress(); }
  static auto IsConnected() -> bool { return Instance().isConnected(); }

  Wifi(const Wifi& rhs) = delete;
  Wifi& operator=(const Wifi& rhs) = delete;
private:
  Wifi() = default;
  Wifi(Wifi&& rhs) noexcept = delete;
  Wifi& operator=(Wifi&& rhs) noexcept = delete;
  ~Wifi() = default;

  Timestamp mLastConnectAttempt{};
  TimerHandle mStatusCheckHandle{};
  bool mConnected{false}; // Primarily used for logging status changes

  static auto Instance() -> Wifi& {
    static Wifi instance;
    return instance;
  }

  auto start() -> int;
  auto update() -> void;
  auto getStatus() const -> int;
  auto getAddress() const -> IPAddress;
  auto restartWifi(WifiStatus status) -> void;
  auto isConnected() const -> bool;

  static auto mapToString(WifiStatus reason) -> const char*;
};

}

#endif //defined(RGB_ARDUINO_ESP32)

#endif //RGBLIB_WIRELESS_H
