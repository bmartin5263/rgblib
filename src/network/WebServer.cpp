//
// Created by Brandon on 2/17/25.
//

#include "WebServer.h"
#include "Wireless.h"

namespace rgb {

auto WebServer::Instance() -> WebServer& {
  static WebServer instance;
  return instance;
}

auto WebServer::Start() -> void {
  Instance().start();
}

auto WebServer::start() -> void {
  if (started) {
    return;
  }
  Wifi::Start();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Arduino Nano ESP32 Web Server: New request received:");
    Serial.println("GET /");
    request->send(200, "text/html", "<html><body><h1>Hello, Arduino Nano ESP32!</h1></body></html>");
  });

  // Start the server
  server.begin();

  started = true;
}

}