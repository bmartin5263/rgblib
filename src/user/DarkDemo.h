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
#include "AdafruitI2CGamepad.h"
#include "Trigger.h"

using namespace rgb;

constexpr auto LED_COUNT = 64;

auto irReceiver = IRReceiver{};
auto gamepad = AdafruitI2CGamepad{};
auto sensors = std::array {
  Runnable {
    [](){ irReceiver.update(); }
  },
  Runnable {
    [](){ gamepad.update(); }
  }
};

auto leds = std::array<LEDCircuit*, 0> {
};

auto scenes = std::array<Scene*, 1> {
  &NullScene::Instance()
};

TimerHandle handle;
Trigger trigger{[](){
  return gamepad.analogX <= .1f;
}};

auto setup() -> void {
  log::init();
  AppBuilder::Create()
    .SetScenes(scenes)
    .SetLEDs(leds)
    .SetSensors(sensors)
    .Start();

  irReceiver.start(D3);
  gamepad.start();
  gamepad.buttonA.onPress([](){ PRINTF("Button A"); });
  gamepad.buttonB.onPress([](){ PRINTF("Button B"); });
  gamepad.buttonX.onPress([](){ PRINTF("Button X"); });
  gamepad.buttonY.onPress([](){ PRINTF("Button Y"); });
  gamepad.buttonStart.onPress([](){ PRINTF("Button Start"); });
  gamepad.buttonSelect.onPress([](){ PRINTF("Button Select"); });
}

auto loop() -> void {
  App::Loop();
  if (trigger.test()) {
    PRINTF("LEFT");
  }
}

#endif //RGBLIB_DEMO1_H
