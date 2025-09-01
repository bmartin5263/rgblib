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
#include "Iterable.h"
#include "LEDMatrix.h"
#include "DataSet.h"
#include "Brightness.h"
#include "PixelSlice.h"

using namespace rgb;

constexpr auto STARTUP_DELAY = Duration::Milliseconds(0);
constexpr auto INTRO_LENGTH = Duration::Seconds(5);

constexpr auto LED_COUNT = 64;
constexpr auto LED_ROWS = 8;
constexpr auto LED_COLUMNS = 8;
constexpr auto LED_TYPE = NEO_GRBW + NEO_KHZ800;   // RGBW
constexpr auto LED_PIN = D2_RGB;
constexpr auto IR_PIN = D3;

auto vehicle = Vehicle{};
auto irReceiver = IRReceiver{};
auto sensors = std::array {
  Runnable { []() {
    irReceiver.update();
  }}
};

auto circuit = LEDMatrix<LED_COLUMNS, LED_ROWS>{LED_PIN, LED_TYPE};
//auto circuit = LEDStrip<LED_COUNT>{LED_PIN, LED_TYPE};
auto slice = circuit.slice(LED_COUNT / 2);
auto leds = std::array {
  static_cast<LEDCircuit*>(&circuit)
};

auto introScene = IntroScene{circuit, NullPixelList::Instance()};
auto demoScene = DemoScene{circuit, irReceiver};
auto scenes = std::array {
  static_cast<Scene*>(&demoScene),
  static_cast<Scene*>(&introScene)
};

auto setup() -> void {
  log::init();
  delay(STARTUP_DELAY.asMilliseconds());

  irReceiver.buttonRight.onPress([](){ App::NextScene(); });
  irReceiver.buttonLeft.onPress([](){ App::PrevScene(); });
  irReceiver.buttonUp.onPress([](){ Brightness::IncreaseLevel(); });
  irReceiver.buttonDown.onPress([](){ Brightness::DecreaseLevel(); });
  irReceiver.buttonHash.onPress([](){ Brightness::SetLevel(BrightnessLevel::DIM); });
  irReceiver.start(IR_PIN);

  DebugScreen::Start(FlipDisplay(true));

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
