//
// Created by Brandon on 2/17/25.
//

#include "Wireless.h"
#include <WiFi.h>

namespace rgb {

auto Wifi::Instance() -> Wifi& {
  static Wifi instance;
  return instance;
}

auto Wifi::Start() -> void {
  Instance().start();
}

auto Wifi::start() -> void {
  if (started) {
    return;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(NAME, PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Retrying...");
    delay(1000);
    // TODO - max attempts w/ error handling
  }
  started = true;
}
}