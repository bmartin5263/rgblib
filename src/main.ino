#include "App.h"
#include "user/RpmDisplay.h"

using namespace rgb;

RpmDisplay scene;

void setup() {
  App::Init(scene);
}

void loop() {
  App::Loop();
}
