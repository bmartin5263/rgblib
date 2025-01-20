#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "App.hpp"
#include "user/DemoScene.h"

Adafruit_NeoPixel circuit(16, D2, NEO_GRBW + NEO_KHZ800);
DemoScene demoScene;

void setup() {
  App::Init(demoScene);
}

void loop() {
  App::Loop();
}