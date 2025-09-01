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
    led = c * Brightness::GetBrightness(1.0f);
  };
  trailingEffect.trailRatio = .3f;
  trailingEffect.speed = Duration::Milliseconds(100);
//  trailingEffect.speed = Duration::Seconds(2);
//  trailingEffect.endBuffer = 20;
  trailingEffect.shader = [](auto& led, auto& params) {
    auto t = (Clock::Now() % Duration::Seconds(1)).value;
    auto p = LerpWrap(0.0f, 1.0f, (static_cast<float>(t) / Duration::Seconds(1).value));
    auto c  = Color::HslToRgb(p);
//    auto c  = Color::PURPLE();
    led = c * Brightness::GetBrightness(1.0f);
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