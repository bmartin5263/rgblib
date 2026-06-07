// #include "lincoln/LincolnApplication.h"
// auto app = LincolnApplication{};

#include "app/CorvetteMetalArtApplication.h"
auto app = CorvetteMetalArtApplication{};

//#include "app/SandboxApplication.h"
//auto app = SandboxApplication{};

auto setup() -> void {
  delay(1000);
  app.setup();
}

auto loop() -> void {
  app.loop();
}