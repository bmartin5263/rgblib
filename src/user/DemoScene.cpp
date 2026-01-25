//
// Created by Brandon on 4/19/25.
//

#include "DemoScene.h"
#include "PixelList.h"

using namespace rgb;

DemoScene::DemoScene(rgb::PixelList& ring, rgb::IRReceiver& irReceiver)
  : ring(ring), irReceiver(irReceiver) {

  fillEffect.shader = [&](auto& pixel, auto& params){
    pixel = color;
  };

  fillEffect.shader = [&](auto& pixel, auto& params){
    const auto SPEED = Duration::Seconds(20);
    auto time = Clock::Now().mod(SPEED).to<float>() / SPEED.to<float>();
    auto hue = LerpWrap(0.0f, 1.0f, time);
    pixel = Color::HslToRgb(hue) * .3f;
//    pixel = Color(1.0f, 0.0f, .2f) * .1f;
  };

}

auto DemoScene::setup() -> void {
  irReceiver.button1.onPress([&](){
    color.r = min(1.0f, color.r + .1f);
  });
  irReceiver.button4.onPress([&](){
    color.r = Brightness::GetBrightness(1.0f);
  });
  irReceiver.button7.onPress([&](){
    color.r = max(0.0f, color.r - .1f);
  });

  irReceiver.button2.onPress([&](){
    color.g = min(1.0f, color.g + .1f);
  });
  irReceiver.button5.onPress([&](){
    color.g = Brightness::GetBrightness(1.0f);
  });
  irReceiver.button8.onPress([&](){
    color.g = max(0.0f, color.g - .1f);
  });

  irReceiver.button3.onPress([&](){
    color.b = min(1.0f, color.b + .1f);
  });
  irReceiver.button6.onPress([&](){
    color.b = Brightness::GetBrightness(1.0f);
  });
  irReceiver.button9.onPress([&](){
    color.b = max(0.0f, color.b - .1f);
  });
}

auto DemoScene::update() -> void {

}

auto DemoScene::draw() -> void {
//  fillEffect.draw(ring);
  auto size = ring.getSize();
  for (int i = 0; i < size; i += 1) {
    ring[i] = Color::GREEN();
//    if (i + 1 < size) {
//      ring[i + 1] = Color::RED();
//    }
//    if (i + 2 < size) {
//      ring[i + 2] = Color::GREEN();
//    }
  }
}