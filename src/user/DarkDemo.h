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
#include "IRReceiver.h"
#include "App.h"
#include "AppBuilder.h"
#include "VehicleThread.h"
#include "AppBuilder.h"
#include "Iterable.h"
#include "LEDMatrix.h"
#include "NullScene.h"
#include "Trigger.h"

using namespace rgb;

constexpr auto LED_COUNT = 64;

auto irReceiver = IRReceiver{};
auto sensors = std::array {
  Runnable {
    [](){ irReceiver.update(); }
  }
};

auto leds = std::array<LEDCircuit*, 0> {
};

auto scenes = std::array<Scene*, 1> {
  &NullScene::Instance()
};

TimerHandle handle;

auto setup() -> void {
  log::init();
  AppBuilder::Create()
    .SetScenes(scenes)
    .SetLEDs(leds)
    .SetSensors(sensors)
    .Start();

  handle = Timer::SetTimeout(Duration::Seconds(1), [](TimerContext& context){
    INFO("Hello");
    context.repeatIn = Duration::Seconds(1);
  });
  handle.onCancel([](){ INFO("Goodbye!"); });

  irReceiver.buttonOk.onPress([](){
    handle.cancel();
  });

  irReceiver.start(D3);
}

auto loop() -> void {
  App::Loop();
}

#endif //RGBLIB_DEMO1_H
