#include "App.h"
#include "user/BasicScene.h"

using namespace rgb;

BasicScene scene;

void setup() {
  App::Init(scene);
}

void loop() {
  App::Loop();
}
