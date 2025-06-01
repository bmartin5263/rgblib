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
#include "AnalogStick.h"
#include "Every.h"

using namespace rgb;

constexpr auto LED_COUNT = 12;

auto ring = LEDCircuit<LED_COUNT>{D2_RGB};
auto slice = ring.slice(3);
auto stick = LEDCircuit<64>{D4_RGB};
auto vehicle = Vehicle{};
auto introScene = IntroScene{ring, stick};
auto demoScene = DemoScene{ring, stick};
auto scenes = std::array {
  static_cast<Scene*>(&demoScene),
  static_cast<Scene*>(&introScene)
};

auto irReceiver = IRReceiver{D3_RGB};
auto analogStick = AnalogStick{22, 23, 24};
auto sensors = std::array {
  Runnable { []() {
    irReceiver.update();
  }},
  Runnable { []() {

  }}
};


auto leds = std::array {
  static_cast<Drawable*>(&ring),
  static_cast<Drawable*>(&stick)
};

auto setup() -> void {
  log::init();

  irReceiver.button0.onPress([](){ App::NextScene(); });
  irReceiver.start();

  DebugScreen::Start();
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

auto doSomething = Every(Duration::Milliseconds(100), [](){
  char buffer[60];
  snprintf(buffer, 60, "x: %i, y: %i", analogStick.readX(), analogStick.readY());
  DebugScreen::PrintLine(0, buffer);
});

auto loop() -> void {
  if (DebugScreen::ReadyForUpdate()) {
//    updateDisplay();
    DebugScreen::Display();
  }
  doSomething.update();
  App::Loop();
}