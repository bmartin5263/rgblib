// #include "lincoln/LincolnApplication.h"
// auto app = LincolnApplication{};

#include "corvette/CorvetteMain.h"
auto app = CorvetteApplication{};

// #include "app/CorvetteMetalArtApplication.h"
// auto app = CorvetteMetalArtApplication{};

// #include "app/RGBPatternApplication.h"
// auto app = RGBPatternApplication{};

//#include "app/SandboxApplication.h"
//auto app = SandboxApplication{};

auto setup() -> void {
  app.setup();
}

auto loop() -> void {
  app.loop();
}