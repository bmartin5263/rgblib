//
// Created by Brandon on 1/5/25.
//

#include "DemoScene.h"
#include "effect/SolidColorGenerator.h"

static SolidColorGenerator solidColorGenerator{Color::CYAN()};

auto DemoScene::setup() -> void {
  neoPixel.begin();
  neoPixel.setBrightness(10);
}

auto DemoScene::update() -> void {
  trailingEffect.update();
}

auto DemoScene::draw() -> void {
  fillEffect.draw(ring, solidColorGenerator);
  trailingEffect.draw(ring, solidColorGenerator);

  circuit.display();
}