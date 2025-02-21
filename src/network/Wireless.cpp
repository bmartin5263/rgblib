//
// Created by Brandon on 2/17/25.
//

#include "Wireless.h"
#include "Log.h"
#include <WiFi.h>

namespace rgb {

auto Wifi::Instance() -> Wifi& {
  static Wifi instance;
  return instance;
}

auto Wifi::Start() -> bool {
  return Instance().start();
}

auto Wifi::start() -> bool {
  if (started) {
    return true;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(NAME, PASSWORD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.disconnect(true, false);
    return false;
  }

  Log.infoLn("WIFI Started");

  started = true;
  return started;
}

}