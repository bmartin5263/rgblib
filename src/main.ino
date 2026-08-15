// #include "lincoln/LincolnApplication.h"
// auto app = LincolnApplication{};

// #include "corvette/CorvetteMain.h"
// auto app = CorvetteApplication{};

#include "app/SandboxApplication.h"
auto app = SandboxApplication{};

// #include "app/RGBPatternApplication.h"
// auto app = RGBPatternApplication{};

// #include "app/SandboxApplication.h"
// auto app = SandboxApplication{};

// #include "app/ExampleApplication.h"
// auto app = ExampleApplication{};

// #include "app/CANSniffingApplication.h"
// auto app = CANSniffingApplication{};

auto setup() -> void {
  // delay(1000);
  app.setup();
}

auto loop() -> void {
  app.loop();
}