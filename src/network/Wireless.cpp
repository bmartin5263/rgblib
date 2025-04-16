//
// Created by Brandon on 2/17/25.
//

#include "Wireless.h"
#include "Log.h"
#include "time/Stopwatch.h"
#include <WiFi.h>

namespace rgb {

auto Wifi::Instance() -> Wifi& {
  static Wifi instance;
  return instance;
}

auto Wifi::Start() -> bool {
  return Instance().start();
}

auto Wifi::Update() -> void {
  Instance().update();
}

auto Wifi::SetMode(wifi_mode_t mode) -> void {
  WiFi.mode(mode);
}

auto Wifi::start() -> bool {
  if (started) {
    return true;
  }

  INFO("Starting Wifi");
  Stopwatch sw{"Wifi::start()"};

  WiFi.begin(NAME, PASSWORD);

  return started;
}

auto Wifi::update() -> void {
  if (WiFi.isConnected() && !started) {
    auto address = WiFi.localIP().toString();
    INFO("WIFI connected to %s", address.c_str());
    started = true;
  }
}

}