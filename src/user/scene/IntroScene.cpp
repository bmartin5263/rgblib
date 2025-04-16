//
// Created by Brandon on 1/5/25.
//

#include "IntroScene.h"
#include "time/Clock.h"

IntroScene::IntroScene(rgb::LEDRing& ring) : ring(ring) {

}

auto IntroScene::setup() -> void {
  fillEffect.shader = [](auto& params){
    auto t = (rgb::Clock::Now() % rgb::Duration::Seconds(4)).value;
    auto p = rgb::LerpWrap(0.0f, 1.0f, (static_cast<float>(t) / rgb::Duration::Seconds(4).value));
    auto c  = rgb::Color::HslToRgb(p);
    return rgb::Color::GREEN(.01f);
  };
  trailingEffect.init();
  trailingEffect.offset = 4;
  trailingEffect.speed = rgb::Duration::Milliseconds(30);
  trailingEffect.continuous = true;
  trailingEffect.endBuffer = 20;
  trailingEffect.shader = [](auto& led, auto& params) {
    auto t = (rgb::Clock::Now() % rgb::Duration::Seconds(7)).value;
    auto p = rgb::LerpWrap(0.0f, 1.0f, (static_cast<float>(t) / rgb::Duration::Seconds(7).value));
    auto c  = rgb::Color::HslToRgb(p);
    led = c * .05f;
  };
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