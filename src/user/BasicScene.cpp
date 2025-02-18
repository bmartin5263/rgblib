//
// Created by Brandon on 2/17/25.
//

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// D2 = D5

#include "BasicScene.h"
#include "sensor/PushButton.h"

namespace rgb {

Adafruit_NeoPixel circuit(16, D2, NEO_GRBW + NEO_KHZ800);
int counter = 0;

PushButton button1{D4};
PushButton button2{D6};
PushButton button3{D9};
PushButton button4{D12};

auto BasicScene::setup() -> void {
  circuit.begin();
  circuit.setBrightness(10);
  button1.init();
}

auto BasicScene::update() -> void {
  auto state = button1.update();
  if (state == ButtonState::PRESS) {
    Log::InfoLn("Press1");
  }

  state = button2.update();
  if (state == ButtonState::PRESS) {
    Log::InfoLn("Press2");
  }

  state = button3.update();
  if (state == ButtonState::PRESS) {
    Log::InfoLn("Press3");
  }

  state = button4.update();
  if (state == ButtonState::PRESS) {
    Log::InfoLn("Press4");
  }
}

auto BasicScene::draw() -> void {
  circuit.clear();

  for (int i = 0; i < 6; ++i) {
    auto c = (counter + i) % 16;
    circuit.setPixelColor(c, 100, 50, 0, 0);
  }
  for (int i = 6; i < 16; ++i) {
    auto c = (counter + i) % 16;
    circuit.setPixelColor(c, 50, 50, 0, 0);
  }
  counter = (counter + 1) % 16;

  circuit.show();
  delay(100);
}

}
