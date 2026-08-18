//
// Created by Brandon on 2/16/25.
//

#include "OTASupport.h"

#if defined(RGB_ARDUINO_ESP32)

#include "ArduinoOTA.h"
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

  INFO("Starting OTA Support");
#if RGB_DEBUG
  Stopwatch sw{"OTASupport::start()"};
#endif

  ArduinoOTA
    .setPort(3232)
    .setMdnsEnabled(false)
    .begin();

  started = true;

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

#endif //defined(RGB_ARDUINO_ESP32)