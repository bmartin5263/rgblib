#include "app/OptimizationApplication.h"

auto app = OptimizationApplication{};

#include "System.h"
#include "Log.h"

auto setup() -> void {
  rgb::log::init();
//  rgb::System::MilliSleep(1000);
  INFO("Setup");
  app.setup();
}

auto loop() -> void {
  app.loop();
}