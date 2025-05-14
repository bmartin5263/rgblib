//
// Created by Brandon on 5/12/25.
//

#ifndef RGBLIB_LINCOLNLIGHTSAPP_H
#define RGBLIB_LINCOLNLIGHTSAPP_H

#include <bitset>
#include "PushButton.h"
#include "Timer.h"
#include "user/lincoln/scene/RpmDisplay.h"
#include "user/SceneManager.h"
#include "user/lincoln/scene/SolidScene.h"
#include "user/lincoln/scene/TrailingScene.h"
#include "user/LEDManager.h"
#include "user/SensorManager.h"
#include "DebugScreen.h"
#include "user/lincoln/scene/IntroScene.h"
#include "user/lincoln/scene/DebugScene.h"
#include "IRReceiver.h"

class LincolnLightsApp {
public:
  auto setup() -> void;
  auto loop() -> void;
  auto updateDisplay() -> void;

private:
  static constexpr rgb::u16 LED_COUNT = 16;

// Output
  rgb::LEDCircuit<LED_COUNT> ring{D5};
  rgb::LEDSlice slice{ring.slice(4)};
  LEDManager<LED_COUNT> ledManager{ring};

// Scenes
  rgb::Vehicle vehicle{};
  RpmDisplay rpmDisplay{ring, vehicle};
  SolidScene solidScene{slice};
  IntroScene introScene{ring};
  DebugScene debugScene{ring, vehicle};
  TrailingScene trailingScene = TrailingScene { TrailingSceneParameters {
    .leds = &ring,
//  .colorGenerator = [](TrailingSceneColorGeneratorParameters params){
//    auto rpm = vehicle.rpm();
//    auto r = LerpClamp(0.0f, 1.0f, rpm, 4000.0f);
//    auto g = LerpClamp(1.0f, 0.0f, rpm, 4000.0f);
//    auto b = 0.0f;
//    auto brightness = LerpClamp(.02f, .03f, rpm, 4000.0f);
//    auto x = Pulse(params.now.asSeconds(), 1.f);
//    brightness += LerpClamp(0.f, .05f, x);
//
//    return Color {1.0f - x, 1.0f, 1.0f - x} * brightness;
//  },
//  .colorGenerator = [](TrailingSceneColorGeneratorParameters params){
//    auto r = LerpClamp(1.0f, .75f, vehicle.rpm() - 600, 3500.0f);
//    auto g = 0.0f;
//    auto b = LerpClamp(0.0f, .25f, vehicle.rpm() - 600, 3500.0f);
//    return Color { r, g, b } * .05f;
//  },
    .colorGenerator = [](TrailingSceneColorGeneratorParameters params){
      auto x = rgb::Pulse(params.now.asSeconds(), .5f);
      auto rgb = rgb::Color::HslToRgb(x) * .02f;
      return rgb;
    },
    .speed = rgb::Duration::Milliseconds(500),
    .shift = 6,
    .length = 6,
    .endBuffer = 4,
    .continuous = true
  }};

  std::array<rgb::Scene*, 3> scenes{
    static_cast<rgb::Scene*>(&rpmDisplay),
    static_cast<rgb::Scene*>(&trailingScene),
    static_cast<rgb::Scene*>(&debugScene)
  };
  SceneManager<3> sceneManager{scenes, &introScene, rgb::Duration::Seconds(2)};

// Input
  rgb::PushButton nextSceneButton{D3, [this](){
    INFO("Next Scene");
    sceneManager.nextScene();
  }};
  rgb::PushButton actionButton{D4, [this](){
    INFO("Action");
    if (rpmDisplay.layout == RpmLayout::SPORT) {
      rpmDisplay.layout = RpmLayout::TRADITIONAL;
    }
    else {
      rpmDisplay.layout = RpmLayout::SPORT;
    }
  }};
  rgb::PushButton toggleLowPower{D5, [this](){
    rpmDisplay.bright = !rpmDisplay.bright;
  }};
  rgb::IRReceiver irReceiver;


  std::array<SensorFunction, 2> sensors = std::array {
    SensorFunction { [this]() {
      static auto lastVehicleUpdate = rgb::Timestamp{};
      if (rgb::Clock::Now().timeSince(lastVehicleUpdate) > rgb::config::VEHICLE_REFRESH_RATE) {
        vehicle.update();
        lastVehicleUpdate = rgb::Clock::Now();
      }
    }},
    SensorFunction { [this]() {
      irReceiver.update();
    }}
  };
  SensorManager<2> sensorManager{ sensors };
};


#endif //RGBLIB_LINCOLNLIGHTSAPP_H
