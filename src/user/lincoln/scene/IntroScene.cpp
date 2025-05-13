//
// Created by Brandon on 1/5/25.
//

#include "IntroScene.h"
#include "Clock.h"

IntroScene::IntroScene(rgb::LEDRing& ring) : ring(ring) {

}

auto IntroScene::setup() -> void {
  fillEffect.shader = [](auto& led, auto& params){
    auto t = (rgb::Clock::Now() % rgb::Duration::Seconds(4)).value;
    auto p = rgb::LerpWrap(0.0f, 1.0f, (static_cast<float>(t) / rgb::Duration::Seconds(4).value));
    auto c  = rgb::Color::HslToRgb(p);
    led = rgb::Color::GREEN(.01f);
  };
  trailingEffect.offset = 4;
  trailingEffect.trailRatio = 6.0f / 12;
  trailingEffect.speed = rgb::Duration::Milliseconds(30);
//  trailingEffect.speed = rgb::Duration::Seconds(2);
//  trailingEffect.endBuffer = 20;
  trailingEffect.shader = [](auto& led, auto& params) {
    auto t = (rgb::Clock::Now() % rgb::Duration::Seconds(1)).value;
//    auto p = rgb::LerpWrap(0.0f, 1.0f, params.positionRatio);
    auto p = rgb::LerpWrap(0.0f, 1.0f, (static_cast<float>(t) / rgb::Duration::Seconds(1).value));
//    auto c  = rgb::Color::BLUE();
//    if (params.relativePosition == 0) {
//      c = rgb::Color::RED();
//    }
    auto c  = rgb::Color::HslToRgb(p);
    led = c * .03f;
  };
  trailingEffect.init();
}

auto IntroScene::update() -> void {
  trailingEffect.update();
}

auto IntroScene::draw() -> void {
//  fillEffect.draw(ring);
  trailingEffect.draw(ring);
}

auto IntroScene::cleanup() -> void {

}