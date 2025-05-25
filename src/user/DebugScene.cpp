//
// Created by Brandon on 4/19/25.
//

#include "DebugScene.h"

DebugScene::DebugScene(rgb::LEDChain& ring, rgb::Vehicle& vehicle): ring(ring), vehicle(vehicle) {

}

auto DebugScene::setup() -> void {
  fillEffect.shader = [&](auto& led, auto& params) {
    led = color;
  };
}

auto DebugScene::update() -> void {

}

auto DebugScene::draw() -> void {
  fillEffect.draw(ring);
}