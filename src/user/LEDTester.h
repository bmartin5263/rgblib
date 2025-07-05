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
#include "Brightness.h"

using namespace rgb;

constexpr auto STARTUP_DELAY = Duration::Milliseconds(0);
constexpr auto INTRO_LENGTH = Duration::Seconds(10);
constexpr auto LED_COUNT = 8;

constexpr auto LED_TYPE = NEO_GRBW + NEO_KHZ800;   // RGBW
constexpr auto LED_PIN = D4_RGB;
constexpr auto IR_PIN = D3;

auto vehicle = Vehicle{};
auto irReceiver = IRReceiver{};
auto sensors = std::array {
  Runnable { []() {
    irReceiver.update();
  }}
};

//auto circuit = LEDMatrix<8, 8>{D2_RGB, NEO_GRBW + NEO_KHZ800};
auto circuit = LEDStrip<LED_COUNT>{LED_PIN, LED_TYPE};
auto slice = circuit.slice(LED_COUNT / 2);
auto leds = std::array {
  static_cast<LEDCircuit*>(&circuit)
};

auto introScene = IntroScene{circuit, NullPixelList::Instance()};
auto demoScene = DemoScene{circuit};
auto scenes = std::array {
  static_cast<Scene*>(&demoScene),
  static_cast<Scene*>(&introScene)
};

auto setup() -> void {
  log::init();
  delay(STARTUP_DELAY.asMilliseconds());

  irReceiver.button0.onPress([](){ App::NextScene(); });
  irReceiver.buttonUp.onPress([](){ Brightness::Increase(); });
  irReceiver.buttonDown.onPress([](){ Brightness::Decrease(); });
  irReceiver.start(IR_PIN);

  DebugScreen::Start(FlipDisplay(true));

  Brightness::Configure()
      .MinBrightness(0.0f)
      .MaxBrightness(.2f)
      .DefaultBrightness(.05f)
      .Step(.05f);

  AppBuilder::Create()
    .DebugOutputLED(&slice)
    .EnableIntroScene(introScene, INTRO_LENGTH)
    .SetScenes(scenes)
    .SetLEDs(leds)
    .SetSensors(sensors)
    .Start();
}

auto loop() -> void {
  App::Loop();
}

#endif //RGBLIB_DEMO1_H
