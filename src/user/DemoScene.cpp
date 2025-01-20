//
// Created by Brandon on 1/5/25.
//

#include "DemoScene.h"
#include "effect/SolidColorGenerator.h"
#include "Debug.h"

static SolidColorGenerator solidColorGenerator{Color::CYAN()};

auto DemoScene::setup() -> void {
  neoPixel.begin();
  neoPixel.setBrightness(10);

  Debug::Instance().setDebugChain(ring);

  auto x = [](const Parameters& params){
    return solidColorGenerator.generate(params);
  };
  trailingEffect.setColorGenerator(x);

  breatheEffect.setHighColor(Color::BLUE())
               .setLowColor(Color::RED())
               .setSpeed(100);


}

auto DemoScene::update() -> void {
  trailingEffect.update();
}

auto DemoScene::draw() -> void {
  fillEffect.draw(*ring, solidColorGenerator);
  trailingEffect.draw(*ring, solidColorGenerator);

  circuit.display();
}

auto DemoScene::cleanup() -> void {
  Debug::Instance().setDebugChain(nullptr);
}