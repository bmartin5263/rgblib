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
}

auto DemoScene::setup() -> void {
  irReceiver.button1.onPress([&](){
    color.r = min(1.0f, color.r + .1f);
  });
  irReceiver.button4.onPress([&](){
    color.r = Brightness::Current();
  });
  irReceiver.button7.onPress([&](){
    color.r = max(0.0f, color.r - .1f);
  });

  irReceiver.button2.onPress([&](){
    color.g = min(1.0f, color.g + .1f);
  });
  irReceiver.button5.onPress([&](){
    color.g = Brightness::Current();
  });
  irReceiver.button8.onPress([&](){
    color.g = max(0.0f, color.g - .1f);
  });

  irReceiver.button3.onPress([&](){
    color.b = min(1.0f, color.b + .1f);
  });
  irReceiver.button6.onPress([&](){
    color.b = Brightness::Current();
  });
  irReceiver.button9.onPress([&](){
    color.b = max(0.0f, color.b - .1f);
  });
}

auto DemoScene::update() -> void {

}

auto DemoScene::draw() -> void {
  fillEffect.draw(ring);
}