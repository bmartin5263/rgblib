//
// Created by Brandon on 2/16/25.
//

#include "OTASupport.h"

#include <WiFi.h>
#include <ArduinoOTA.h>
#include <ESPAsyncWebServer.h>
#include "Wireless.h"
#include "Stopwatch.h"
#include "Log.h"

namespace rgb {

auto OTASupport::Start() -> bool {
  return Instance().start();
}

auto OTASupport::start() -> bool {
  if (started) {
    return true;
  }
  if (!Wifi::Start()) {
    return false;
  }

  INFO("Starting OTA Support");
  Stopwatch sw{"OTASupport::start()"};

  ArduinoOTA
    .setPort(3232)
    .setHostname("myesp32")
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        Serial.println("type = sketch");
        type = "sketch";
      } else {  // U_SPIFFS
        Serial.println("type = filesystem");
        type = "filesystem";
      }

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("End");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        Serial.println("Auth Failed");
      } else if (error == OTA_BEGIN_ERROR) {
        Serial.println("Begin Failed");
      } else if (error == OTA_CONNECT_ERROR) {
        Serial.println("Connect Failed");
      } else if (error == OTA_RECEIVE_ERROR) {
        Serial.println("Receive Failed");
      } else if (error == OTA_END_ERROR) {
        Serial.println("End Failed");
      }
    })
    .begin();

  started = true;
  digitalWrite(LED_BLUE, LOW);

  return started;
}

auto OTASupport::Update() -> void {
  Instance().update();
}

auto OTASupport::update() -> void {
  if (!started) {
    return;
  }
  ArduinoOTA.handle();
}

auto OTASupport::Instance() -> OTASupport& {
  static OTASupport instance;
  return instance;
}

}