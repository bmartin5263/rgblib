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
#include "NullScene.h"

using namespace rgb;

constexpr auto LED_COUNT = 64;

auto sensors = std::array<Runnable, 0> {
};

auto leds = std::array<LEDCircuit*, 0> {
};

auto scenes = std::array<Scene*, 1> {
  &NullScene::Instance()
};

TimerHandle handle;

auto setup() -> void {
  delay(2000);
  log::init();
  AppBuilder::Create()
    .SetScenes(scenes)
    .SetLEDs(leds)
    .SetSensors(sensors)
    .Start();

  Timer::ContinuouslyFor(Duration::Seconds(5), [runs = 0](TimerContext& context) mutable {
    INFO("Step 1: %f %i", context.percentComplete, ++runs);
    if (context.percentComplete >= 1.0f) {
      Timer::ContinuouslyFor(Duration::Seconds(1), [runs = 0](TimerContext& context) mutable {
        INFO("Step 2: %f %i", context.percentComplete, ++runs);
      }).release();
    }
  }).release();
}

auto loop() -> void {
  App::Loop();
}

#endif //RGBLIB_DEMO1_H
