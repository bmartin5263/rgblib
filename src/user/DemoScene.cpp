//
// Created by Brandon on 1/5/25.
//

#include "DemoScene.h"
#include "Debug.h"

namespace rgb {

auto DemoScene::setup() -> void {
//  neoPixel.begin();
//  neoPixel.setBrightness(10);

//  Debug::Instance().setDebugChain(ring);

//  trailingEffect.setLength(5)
//                .setSpeed(10)
//                .setColorGenerator(Generator{
//                  return Color::RED();
//                });
//
//  breatheEffect.setHighColor(Color::BLUE())
//               .setLowColor(Color::RED())
//               .setSpeed(100);
//
//  fillEffect.setColorGenerator(Generator{
//              return Color::RED();
//            });

  neoPixel.begin();
  neoPixel.setBrightness(10);
}

auto DemoScene::update() -> void {
  neoPixel.clear();
  neoPixel.setBrightness(10);
//  circuit.fill(Color::MAGENTA());
//  trailingEffect.update();
  for (int i = 0; i < 16; ++i) {
    neoPixel.setPixelColor(i, 0, 20, 20, 0);
  }
  Serial.println(neoPixel.getBrightness());
}

auto DemoScene::draw() -> void {
//  fillEffect.draw(*ring);
//  trailingEffect.draw(*ring);

//  circuit.display();
  neoPixel.show();
}

auto DemoScene::cleanup() -> void {
//  Debug::Instance().setDebugChain(nullptr);
}

}