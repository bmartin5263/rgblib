//
// Created by Brandon on 4/19/25.
//

#include "DebugScene.h"

DebugScene::DebugScene(rgb::LEDChain& ring, rgb::Vehicle& vehicle): ring(ring), vehicle(vehicle) {

}

auto DebugScene::setup() -> void {
//  fillEffect.shader = [&](auto& led, auto& params){
//    float rpm = vehicle.rpm();
//    auto fuelLevel = vehicle.fuelLevel();
//    auto coolantTemp = rgb::LerpClamp(.0f, 1.0f, rpm / 10'000);
////    auto duration = rgb::Duration::Milliseconds(rpm);
////    auto time = (rgb::Clock::Now() % duration).value;
////    auto hue = rgb::LerpWrap(0.0f, 1.0f, (static_cast<float>(time) / duration.value));
////    led = rgb::Color::HslToRgb(hue) * .05f;
//    auto c  = rgb::Color::HslToRgb(fuelLevel);
//    led = c * coolantTemp;
//  };
  fillEffect.shader = [&](auto& led, auto& params){
    float rpm = vehicle.rpm();
    auto fuelLevel = vehicle.fuelLevel();
    auto coolantTemp = rgb::LerpClamp(.0f, 1.0f, rpm / 10'000);
//    auto duration = rgb::Duration::Milliseconds(rpm);
//    auto time = (rgb::Clock::Now() % duration).value;
//    auto hue = rgb::LerpWrap(0.0f, 1.0f, (static_cast<float>(time) / duration.value));
//    led = rgb::Color::HslToRgb(hue) * .05f;
    auto c  = rgb::Color::HslToRgb(rgb::LerpWrap(0.0f, 1.0f, params.relativePosition() + fuelLevel));
    led = c * coolantTemp;
  };
}

auto DebugScene::update() -> void {

}

auto DebugScene::draw() -> void {
  fillEffect.draw(ring);
}