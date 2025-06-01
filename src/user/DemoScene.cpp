//
// Created by Brandon on 4/19/25.
//

#include "DemoScene.h"
#include "LEDChain.h"

using namespace rgb;

DemoScene::DemoScene(rgb::LEDChain& ring, rgb::LEDChain& stick)
  : ring(ring), stick(stick) {

}

auto DemoScene::setup() -> void {
  fillEffect.shader = [&](auto& led, auto& params) {
    led = rgb::Color::HslToRgb(params.relativePosition()) * .03f;
  };
}

auto DemoScene::update() -> void {

}

auto DemoScene::draw() -> void {
  fillEffect.draw(ring);
//  fillEffect.draw(stick);

//  stick
//    .fill(Color::GREEN(), 4)
//    .fill(Color::YELLOW(), 3)
//    .fill(Color::RED(), 1);

  stick
    .fill(Color::GREEN(), 42)
    .fill(Color::YELLOW(), 18)
    .fill(Color::WHITE(.1f), 4);
}