//
// Created by Brandon on 1/5/25.
//

#include "IntroScene.h"
#include "Clock.h"

using namespace rgb;

IntroScene::IntroScene(PixelRing& ring, PixelStrip& stick) : ring(ring), stick(stick) {

}

auto IntroScene::setup() -> void {
  fillEffect.shader = [](auto& led, auto& params){
    auto t = (Clock::Now() % Duration::Seconds(4)).value;
    auto p = LerpWrap(0.0f, 1.0f, (static_cast<float>(t) / Duration::Seconds(4).value));
    auto c  = Color::HslToRgb(p);
    led = c * .01f;
  };
  trailingEffect.trailRatio = .5f;
  trailingEffect.speed = Duration::Milliseconds(200);
//  trailingEffect.speed = Duration::Seconds(2);
//  trailingEffect.endBuffer = 20;
  trailingEffect.shader = [](auto& led, auto& params) {
    auto t = (Clock::Now() % Duration::Seconds(1)).value;
//    auto p = LerpWrap(0.0f, 1.0f, params.positionRatio);
    auto p = LerpWrap(0.0f, 1.0f, (static_cast<float>(t) / Duration::Seconds(1).value));
//    auto c  = Color::BLUE();
//    if (params.relativePosition == 0) {
//      c = Color::RED();
//    }
    auto c  = Color::HslToRgb(p);
    led = c * .03f;
    led = Color::PURPLE();
  };
  trailingEffect.init();
}

auto IntroScene::update() -> void {
  trailingEffect.update();
}

auto IntroScene::draw() -> void {
//  fillEffect.draw(ring);
  trailingEffect.draw(ring);
  trailingEffect.draw(stick);
}

auto IntroScene::cleanup() -> void {

}