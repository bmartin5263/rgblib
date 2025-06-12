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
#include "ColorFactory.h"

using namespace rgb;

constexpr auto LED_COUNT = 12;

auto circuit = LEDStrip<LED_COUNT>{D2_RGB};
auto leds = std::array {
  static_cast<LEDCircuit*>(&circuit)
};

auto demoScene = DemoScene{circuit};
auto scenes = std::array {
  static_cast<Scene*>(&demoScene)
};

auto colorFactory = ColorFactory{ColorFactory::LEVEL_0};

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
  }).detach();

  Timer::SetTimeout(Duration::Seconds(10), [](auto& context) {
    colorFactory.intensity = ColorFactory::LEVEL_1;
  }).detach();

  demoScene.fillEffect.shader = [](auto& pixel, const auto& params){
    if (params.position == 0) {
      pixel = colorFactory.red();
    }
    else if (params.position == 1) {
      pixel = colorFactory.magenta();
    }
    else if (params.position == 2) {
      pixel = colorFactory.maroon();
    }
    else if (params.position == 3) {
      pixel = colorFactory.orange();
    }
    else if (params.position == 4) {
      pixel = colorFactory.gold();
    }
    else if (params.position == 5) {
      pixel = colorFactory.salmon();
    }
    else if (params.position == 6) {
      pixel = colorFactory.green();
    }
    else if (params.position == 7) {
      pixel = colorFactory.springGreen();
    }
    else if (params.position == 8) {
      pixel = colorFactory.lime();
    }
    else if (params.position == 9) {
      pixel = colorFactory.aquamarine();
    }
    else if (params.position == 10) {
      pixel = colorFactory.indigo();
    }
    else if (params.position == 11) {
      pixel = colorFactory.purple();
    }
    else {
      pixel = colorFactory.red();
    }
  };
}

auto loop() -> void {
  App::Loop();
}

#endif //RGBLIB_DEMO1_H
