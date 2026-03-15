//#include "lincoln/LincolnApplication.h"
#include "app/CorvetteMetalArtApplication.h"

//auto app = LincolnApplication{};
auto app = CorvetteMetalArtApplication{};

auto setup() -> void {
  app.setup();
}

auto loop() -> void {
  app.loop();
}