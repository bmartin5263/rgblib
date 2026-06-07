//
// Created by Brandon on 2/17/25.
//

#include <WiFi.h>

#include "Wireless.h"
#include "Log.h"
#include "Stopwatch.h"
#include "Timer.h"
#include "Clock.h"

namespace rgb {

auto Wifi::SetMode(wifi_mode_t mode) -> void {
  WiFiClass::mode(mode);
}

auto Wifi::start() -> int {
  if (auto status = getStatus(); status == WL_CONNECTED || status == WL_IDLE_STATUS) {
    return status;
  }

  static_assert(
    StrLength(SSID) == 0 || StrLength(PASSWORD) > 0,
    "Missing Password - Please define RGB_WIFI_PASSWORD"
  );

  INFO("Starting Wi-Fi using SSID %s", SSID);

  lastConnectAttempt = Clock::Now();
  return WiFi.begin(SSID, PASSWORD); // Expected return is WL_DISCONNECTED while connecting
}

auto Wifi::restartWifi(const char* reason) -> void {
  if (Clock::Now().timeSince(lastConnectAttempt) > Duration::Seconds(5)) {
    ERROR("Failed to connect to Wi-Fi. Reason Code: %s", reason);
    start();
  }
}

auto Wifi::update() -> void {
  switch (WiFiClass::status()) {
    case WL_CONNECTED:
      if (!connected) {
        INFO("Wi-Fi connected with IP %s", WiFi.localIP().toString().c_str());
        connected = true;
      }
      break;
    case WL_IDLE_STATUS:
      // Waiting for connection
      break;
    case WL_NO_SHIELD:
      restartWifi("WL_NO_SHIELD");
      break;
    case WL_CONNECT_FAILED:
      restartWifi("WL_CONNECT_FAILED");
      break;
    case WL_CONNECTION_LOST:
      restartWifi("WL_CONNECTION_LOST");
      break;
    case WL_DISCONNECTED:
      restartWifi("WL_DISCONNECTED");
      break;
    case WL_NO_SSID_AVAIL:
      restartWifi("WL_NO_SSID_AVAIL");
      break;
    case WL_SCAN_COMPLETED:
      restartWifi("WL_SCAN_COMPLETED");
      break;
  }
}

auto Wifi::getStatus() const -> int {
  return WiFiClass::status();
}

auto Wifi::getAddress() const -> String {
  return WiFi.localIP().toString();
}

}