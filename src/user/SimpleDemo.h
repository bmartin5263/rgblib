//
// Created by Brandon on 6/9/25.
//

#ifndef RGBLIB_DEMO1_H
#define RGBLIB_DEMO1_H

#include <bitset>
#include <cstdio>
#include "Timer.h"
#include "LEDStrip.h"
#include "user/DemoScene.h"
#include "App.h"
#include "AppBuilder.h"
#include "Iterable.h"
#include "LEDMatrix.h"
#include "NullScene.h"
#include "DataSet.h"

using namespace rgb;

constexpr auto LED_COUNT = 12;

auto circuit = LEDStrip<LED_COUNT>{D2_RGB, NEO_BRG};
auto leds = std::array {
  static_cast<LEDCircuit*>(&circuit)
};

auto demoScene = DemoScene{circuit};
auto scenes = std::array {
  static_cast<Scene*>(&demoScene)
};

auto dataSet = DataSet<int, 100>{};
auto setup() -> void {
  log::init();
  AppBuilder::Create()
    .SetScenes(scenes)
    .SetLEDs(leds)
    .Start();

  Timer::SetImmediateTimeout([](auto& context){
    dataSet.push((rand() % 1000) + 1);
    context.repeatIn = Duration::Milliseconds(1);
  }).detach();

  Timer::SetTimeout(Duration::Seconds(1), [](auto& context){
    PRINTF("Average: %f", dataSet.average());
    context.repeatIn = Duration::Seconds(1);
  })
  .detach();
}

auto loop() -> void {
  App::Loop();
}

#endif //RGBLIB_DEMO1_H
