#include "lincoln/LincolnApplication.h"
auto app = LincolnApplication{};

//#include "app/CorvetteMetalArtApplication.h"
//auto app = CorvetteMetalArtApplication{};

//#include "app/OptimizationApplication.h"
//auto app = OptimizationApplication{};

auto setup() -> void {
  app.setup();
}

auto loop() -> void {
  app.loop();
}