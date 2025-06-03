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
#include "LEDMatrix.h"

using namespace rgb;

constexpr auto LED_COUNT = 64;

auto vehicle = Vehicle{};
auto irReceiver = IRReceiver{};
auto analogStick = AnalogStick{22, 23, 24};
auto sensors = std::array {
  Runnable { []() {
    irReceiver.update();
  }}
};

auto circuit = LEDCircuit<LED_COUNT>{D2_RGB, 0, NEO_GRB + NEO_KHZ800};
auto grid = LEDMatrix<8, 8>{D2_RGB, 0, NEO_GRB + NEO_KHZ800};
auto slice = circuit.slice(3);
auto stick = LEDCircuit<64>{D4_RGB};
auto leds = std::array {
  static_cast<LEDList*>(&circuit),
  static_cast<LEDList*>(&stick)
};

auto introScene = IntroScene{circuit, stick};
auto demoScene = DemoScene{circuit, stick};
auto scenes = std::array {
  static_cast<Scene*>(&demoScene),
  static_cast<Scene*>(&introScene)
};

auto setup() -> void {
  log::init();

  irReceiver.button0.onPress([](){ App::NextScene(); });
  irReceiver.start(D3);

  DebugScreen::Start();
  AppBuilder::Create()
    .DebugOutputLED(&slice)
    .EnableIntroScene(introScene, Duration::Seconds(20))
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