//
// Created by Brandon on 2/16/25.
//

#include "OTASupport.h"

#include <ArduinoOTA.h>
#include "Stopwatch.h"
#include "Log.h"
#include "Config.h"

namespace rgb {

auto OTASupport::Start() -> bool {
  return Instance().start();
}

auto OTASupport::start() -> bool {
  if (started) {
    return true;
  }

  INFO("Starting OTA Support");
  Stopwatch sw{"OTASupport::start()"};

  ArduinoOTA
    .setPort(3232)
    .setHostname("myesp32")
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