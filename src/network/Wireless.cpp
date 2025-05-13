//
// Created by Brandon on 2/17/25.
//

#include <WiFi.h>

#include "Wireless.h"
#include "Log.h"
#include "Stopwatch.h"
#include "Config.h"
#include "Timer.h"
#include "Clock.h"

namespace rgb {

auto Wifi::SetMode(wifi_mode_t mode) -> void {
  WiFi.mode(mode);
}

auto Wifi::start() -> int {
  auto status = getStatus();
  if (status == WL_CONNECTED || status == WL_IDLE_STATUS) {
    return status;
  }

  static_assert(
    Length(SSID) == 0 || Length(PASSWORD) > 0,
    "Missing Password - Please define RGB_WIFI_PASSWORD"
  );

  INFO("Starting Wi-Fi using SSID %s %s", SSID, PASSWORD);
  Stopwatch sw{"Wifi::start()"};

  lastConnectAttempt = Clock::Now();
  return WiFi.begin(SSID, PASSWORD); // Expected return is WL_DISCONNECTED while connecting
}

#define RESTART_WIFI(reason) \
if (Clock::Now().timeSince(lastConnectAttempt) > Duration::Seconds(5)) { \
  ERROR("Failed to connect to Wi-Fi. Reason Code: %s", #reason); \
  start();                     \
}

auto Wifi::update() -> void {
  switch (WiFi.status()) {
    case WL_CONNECTED:
      if (!connected) {
        INFO("Wi-Fi connected to %s", WiFi.localIP().toString().c_str());
        connected = true;
        digitalWrite(rgb::config::LED_OTA_CONNECTED, LOW);
      }
      break;
    case WL_IDLE_STATUS:
      // Waiting for connection
      break;
    case WL_NO_SHIELD:
      RESTART_WIFI(WL_NO_SHIELD);
      break;
    case WL_CONNECT_FAILED:
      RESTART_WIFI(WL_CONNECT_FAILED);
      break;
    case WL_CONNECTION_LOST:
      RESTART_WIFI(WL_CONNECTION_LOST);
      break;
    case WL_DISCONNECTED:
      RESTART_WIFI(WL_DISCONNECTED);
      break;
    case WL_NO_SSID_AVAIL:
      RESTART_WIFI(WL_NO_SSID_AVAIL);
      break;
    case WL_SCAN_COMPLETED:
      RESTART_WIFI(WL_SCAN_COMPLETED);
      break;
  }
}

auto Wifi::getStatus() const -> int {
  return WiFi.status();
}

}