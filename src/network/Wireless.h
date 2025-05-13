//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_WIRELESS_H
#define RGBLIB_WIRELESS_H

#include <esp_wifi_types.h>
#include "TimerHandle.h"

namespace rgb {

static constexpr auto Length(const char* string) -> size_t {
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
static constexpr auto ENABLED = rgb::Length(SSID) > 0;

public:
  constexpr static auto Enabled() -> bool {
    return ENABLED;
  }

  static auto SetMode(wifi_mode_t mode) -> void;
  static auto Start() -> int { return Instance().start(); }
  static auto Update() -> void { Instance().update(); }
  static auto GetStatus() -> int { return Instance().getStatus(); }

private:
  Wifi() = default;
  Wifi(const Wifi& rhs) = delete;
  Wifi(Wifi&& rhs) noexcept = default;
  Wifi& operator=(const Wifi& rhs) = delete;
  Wifi& operator=(Wifi&& rhs) noexcept = default;
  ~Wifi() = default;

  Timestamp lastConnectAttempt{};
  TimerHandle statusCheckHandle{};
  bool connected{false}; // Primarily used for logging status changes

  static auto Instance() -> Wifi& {
    static Wifi instance;
    return instance;
  }

  auto start() -> int;
  auto update() -> void;
  auto getStatus() const -> int;
};

}


#endif //RGBLIB_WIRELESS_H
