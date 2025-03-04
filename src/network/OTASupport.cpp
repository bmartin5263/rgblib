//
// Created by Brandon on 2/16/25.
//

#include "OTASupport.h"

#include <WiFi.h>
#include <ArduinoOTA.h>
#include <ESPAsyncWebServer.h>
#include "Wireless.h"

namespace rgb {

auto OTASupport::Start() -> void {
  Instance().start();
}

auto OTASupport::start() -> void {
  if (started) {
    return;
  }
  Wifi::Start();

  // Port defaults to 3232
  ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("myesp32");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      Serial.println("OnStart()");
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
      Serial.println("\nEnd");
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
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  started = true;
}

auto OTASupport::Update() -> void {
  Instance().update();
}

auto OTASupport::update() -> void {
  ArduinoOTA.handle();
}

auto OTASupport::Instance() -> OTASupport& {
  static OTASupport instance;
  return instance;
}

}