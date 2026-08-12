//
// Created by Brandon on 2/17/25.
//

#include <WiFi.h>

#include "Wireless.h"
#include "Log.h"
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

  mLastConnectAttempt = Clock::Now();
  return WiFi.begin(SSID, PASSWORD); // Expected return is WL_DISCONNECTED while connecting
}

auto Wifi::restartWifi(WifiStatus status) -> void {
  if (Clock::Now().timeSince(mLastConnectAttempt) > WIFI_RECONNECT_TIMEOUT) {
    ERROR("Failed to connect to Wi-Fi. Reason Code: %s", mapToString(status));
    start();
  }
}

auto Wifi::isConnected() const -> bool {
  return mConnected;
}

auto Wifi::update() -> void {
  switch (WiFiClass::status()) {
    case WL_CONNECTED:
      if (!mConnected) {
#if RGB_DEBUG
        auto ip = WiFi.localIP();
        INFO("Wi-Fi connected with IP %u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
#endif
        mConnected = true;
      }
      break;
    case WL_IDLE_STATUS:
      // Waiting for connection
      break;
    case WL_NO_SHIELD:
      restartWifi(WL_NO_SHIELD);
      break;
    case WL_CONNECT_FAILED:
      restartWifi(WL_CONNECT_FAILED);
      break;
    case WL_CONNECTION_LOST:
      restartWifi(WL_CONNECTION_LOST);
      break;
    case WL_DISCONNECTED:
      restartWifi(WL_DISCONNECTED);
      break;
    case WL_NO_SSID_AVAIL:
      restartWifi(WL_NO_SSID_AVAIL);
      break;
    case WL_SCAN_COMPLETED:
      restartWifi(WL_SCAN_COMPLETED);
      break;
  }
}

auto Wifi::getStatus() const -> int {
  return WiFiClass::status();
}

auto Wifi::getAddress() const -> IPAddress {
  return WiFi.localIP();
}

auto Wifi::mapToString(WifiStatus reason) -> const char* {
  switch (reason) {
    case WL_CONNECTED:
      return "CONNECTED";
    case WL_IDLE_STATUS:
      return "IDLE";
    case WL_NO_SHIELD:
      return "NO_SHIELD";
    case WL_CONNECT_FAILED:
      return "CONNECT_FAILED";
    case WL_CONNECTION_LOST:
      return "CONNECTION_LOST";
    case WL_DISCONNECTED:
      return "DISCONNECTED";
    case WL_NO_SSID_AVAIL:
      return "NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED:
      return "SCAN_COMPLETED";
    default:
      return "UNKNOWN";
  }
}

}
