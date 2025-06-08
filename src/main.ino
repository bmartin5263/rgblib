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

using namespace rgb;

constexpr auto LED_COUNT = 64;

auto vehicle = Vehicle{};
auto irReceiver = IRReceiver{};
auto sensors = std::array {
  Runnable { []() {
    irReceiver.update();
  }}
};

auto circuit = LEDMatrix<8, 8>{D2_RGB, NEO_GRBW + NEO_KHZ800};
auto slice = circuit.slice(3);
auto stick = LEDStrip<64>{D4_RGB};
auto leds = std::array {
  static_cast<LEDCircuit*>(&circuit),
  static_cast<LEDCircuit*>(&stick)
};

auto introScene = IntroScene{circuit, stick};
auto demoScene = DemoScene{circuit, stick};
auto scenes = std::array {
  static_cast<Scene*>(&demoScene),
  static_cast<Scene*>(&introScene)
};

TimerHandle handle;

auto setup() -> void {
  log::init();
  delay(2000);

  handle = Timer::SetTimeout(Duration::Seconds(1), [x = 0](auto& result) mutable {
    DebugScreen::PrintLine("Hello " + std::to_string(x++));
    DebugScreen::Display();
    result.repeatIn = Duration::Seconds(1);
  });

  INFO("Success");

  irReceiver.button0.onPress([](){ App::NextScene(); });
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