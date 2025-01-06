#include <Arduino.h>
#include "DemoScene.h"
#include "core/App.hpp"

static DemoScene demoScene{};

void setup() {
  App::Init(demoScene);
}

void loop() {
  App::Loop();
}