//
// Created by Brandon on 3/17/25.
//

#include "SolidScene.h"

SolidScene::SolidScene(rgb::LEDChain& leds): leds(leds) {

}

auto SolidScene::update() -> void {
}

auto SolidScene::draw() -> void {
  leds.fill(color);
}