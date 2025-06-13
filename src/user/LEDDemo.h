//
// Created by Brandon on 6/9/25.
//

#ifndef RGBLIB_DEMO1_H
#define RGBLIB_DEMO1_H

#include <bitset>
#include <cstdio>
#include "Timer.h"
#include "DebugScreen.h"
#include "user/IntroScene.h"
#include "user/DemoScene.h"
#include "IRReceiver.h"
#include "App.h"
#include "AppBuilder.h"
#include "VehicleThread.h"
#include "AppBuilder.h"
#include "Iterable.h"
#include "LEDMatrix.h"
#include "DataSet.h"

using namespace rgb;

constexpr auto LED_COUNT = 64;

auto vehicle = Vehicle{};
auto irReceiver = IRReceiver{};
auto sensors = std::array {
  Runnable { []() {
    irReceiver.update();
  }}
};

auto circuit = LEDStrip<64>{D2_RGB, NEO_BRG};
auto slice = circuit.slice(3);
auto leds = std::array {
  static_cast<LEDCircuit*>(&circuit)
};

auto introScene = IntroScene{circuit, NullPixelList::Instance()};
auto demoScene = DemoScene{circuit};
auto scenes = std::array {
  static_cast<Scene*>(&demoScene),
  static_cast<Scene*>(&introScene)
};

auto handle = TimerHandle{};
auto dataSet = DataSet<int, 20>{};

auto setup() -> void {
  log::init();

  INFO("Success");

  irReceiver.button0.onPress([](){ App::NextScene(); });
  irReceiver.button1.onPress([](){
    Timer::ContinuouslyFor(Duration::Seconds(1), [](TimerContext& context) mutable {
      DebugScreen::PrintLine("Hello " + std::to_string(context.percentComplete));
      DebugScreen::Display();
      dataSet.push(10);
    }).detach();
  });
  irReceiver.start(D3);

  DebugScreen::Start(true);
  AppBuilder::Create()
    .DebugOutputLED(&slice)
    .EnableIntroScene(introScene, Duration::Seconds(5))
    .SetScenes(scenes)
    .SetLEDs(leds)
    .SetSensors(sensors)
    .Start();

//  VehicleThread::Instance().autoUpdate = true;
//  VehicleThread::Start(vehicle);
}

auto loop() -> void {
//  if (DebugScreen::ReadyForUpdate()) {
//    DebugScreen::PrintLine("Hello");
//    DebugScreen::Display();
//  }
  App::Loop();
}

#endif //RGBLIB_DEMO1_H
