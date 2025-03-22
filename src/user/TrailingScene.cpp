//
// Created by Brandon on 3/17/25.
//

#include "TrailingScene.h"

TrailingScene::TrailingScene(rgb::LEDChain& leds): leds(leds) {

}

auto TrailingScene::update() -> void {
  if (moveTime++ >= moveRate) {
    move();
    moveTime = 0;
  }
}

auto TrailingScene::draw() -> void {
  auto ledSize = leds.size();
  for (int i = 0; i < 6; ++i) {
    auto p = (pixel + i);
    if (p < ledSize) {
      leds[p] = color;
    }
  }
}

auto TrailingScene::move() -> void {
  pixel += 1;
  if (pixel >= 22) {
    pixel = 0;
  }
}