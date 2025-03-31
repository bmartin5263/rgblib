//
// Created by Brandon on 2/17/25.
//

#include "Wireless.h"
#include "Log.h"
#include "Stopwatch.h"
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
  INFO("Starting Wifi");
  Stopwatch sw{"Wifi::start()"};

  WiFi.begin(NAME, PASSWORD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.disconnect(true, false);
    return false;
  }

  auto address = WiFi.localIP().toString();
  INFO("WIFI connected to %s", address.c_str());

  started = true;
  return started;
}

}