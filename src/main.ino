//#include "lincoln/LincolnApplication.h"
#include "app/CorvetteMetalArtApplication.h"
//#include "app/OptimizationApplication.h"

//auto app = LincolnApplication{};
auto app = CorvetteMetalArtApplication{};
//auto app = OptimizationApplication{};

auto setup() -> void {
  app.setup();
}

auto loop() -> void {
  app.loop();
}