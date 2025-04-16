//
// Created by Brandon on 1/5/25.
//

#include "IntroScene.h"

IntroScene::IntroScene(rgb::LEDRing& ring) : ring(ring) {

}

auto IntroScene::setup() -> void {
  fillEffect.shader = [](auto params){
    auto p = rgb::Pulse(params.now.asSeconds(), 1.2f);
    return rgb::Color::MAGENTA(rgb::LerpClamp(.01f, .02f, p));
  };
  trailingEffect.init();
  trailingEffect.offset = 4;
  trailingEffect.speed = rgb::Duration::Milliseconds(30);
  trailingEffect.continuous = true;
  trailingEffect.endBuffer = 20;
  trailingEffect.shader = [](auto params) {
//    auto amount = rgb::LerpClamp(.005f, .03f, params.positionRatio);
    auto amount = .05f;
    return rgb::Color(amount * .5f, 0.0f, amount);
  };
}

auto IntroScene::update() -> void {
  trailingEffect.update();
}

auto IntroScene::draw() -> void {
  fillEffect.draw(ring);
  trailingEffect.draw(ring);
}

auto IntroScene::cleanup() -> void {

}