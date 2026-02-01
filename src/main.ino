#include "LincolnApplication.h"

auto app = LincolnApplication{};

#include "System.h"
#include "Log.h"

auto setup() -> void {
  rgb::log::init();
//  rgb::System::MilliSleep(1000);
  INFO("Setup");
//  irReceiver.start();
  app.setup();
}

auto loop() -> void {
//  irReceiver.read();
  app.loop();
}