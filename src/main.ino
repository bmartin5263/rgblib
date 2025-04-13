#include <thread>
#include "App.h"
#include "AppBuilder.h"
#include "sensor/PushButton.h"
#include "sensor/ConnectToVehicleCommand.h"
#include "effect/Timer.h"
#include "user/RpmDisplay.h"
#include "user/ChainableScene.h"
#include "user/SceneManager.h"
#include "user/SolidScene.h"
#include "user/TrailingScene.h"
#include "user/LEDManager.h"
#include "user/SensorManager.h"
#include "threading/VehicleThread.h"
#include "screen/DebugScreen.h"

using namespace rgb;

constexpr auto staticAssertions() -> void {
  static_assert(sizeof(i32) > sizeof(u16));
  static_assert(sizeof(i64) > sizeof(u32));
  static_assert(sizeof(int) == 4);
  static_assert(sizeof(int) == sizeof(float));
  static_assert(sizeof(int*) == 4);
  static_assert(sizeof(long) == 4);
  static_assert(sizeof(long long) == 8);
  static_assert(sizeof(float) == 4);
  static_assert(sizeof(double) == 8);
}

constexpr u16 LED_COUNT = 12;

// Output
auto ring = LEDCircuit<LED_COUNT>{D5};
auto slice = ring.slice(6);
auto ledManager = LEDManager<LED_COUNT>{ring};

// Scenes
auto vehicle = Vehicle{};
auto rpmDisplay = RpmDisplay{ring, vehicle};
auto solidScene = SolidScene{slice};

auto trailingScene = TrailingScene{ TrailingSceneParameters {
  .leds = &ring,
  .colorGenerator = [](TrailingSceneColorGeneratorParameters params){
    auto r = LerpClamp(0.0f, 1.0f, vehicle.rpm() - 600, 3500.0f);
    auto g = LerpClamp(1.0f, 0.0f, vehicle.rpm() - 600, 3500.0f);
    auto b = 0.0f;
    return Color { r, g, b } * .03f;
  },
//  .colorGenerator = [](TrailingSceneColorGeneratorParameters params){
//    auto r = LerpClamp(1.0f, .75f, vehicle.rpm() - 600, 3500.0f);
//    auto g = 0.0f;
//    auto b = LerpClamp(0.0f, .25f, vehicle.rpm() - 600, 3500.0f);
//    return Color { r, g, b } * .05f;
//  },
//  .colorGenerator = [](TrailingSceneColorGeneratorParameters params){
//    auto x = Pulse(params.now.asSeconds(), .5f);
//    auto rgb = Color::HslToRgb(x) * .02f;
//    return rgb;
//  },
  .speed = Duration::Milliseconds(500),
  .shift = 6,
  .length = 6,
  .endBuffer = 4,
  .continuous = true
}};

auto scenes = std::array {
  static_cast<Scene*>(&rpmDisplay),
  static_cast<Scene*>(&trailingScene),
//  static_cast<Scene*>(&solidScene)
};
auto sceneManager = SceneManager {scenes, &trailingScene, Duration::Seconds(1)};

// Input
auto nextSceneButton = PushButton{D3, [](){
  INFO("Next Scene");
  sceneManager.nextScene();
}};
auto actionButton = PushButton{D4, [](){
  INFO("Action");
  if (rpmDisplay.layout == RpmLayout::SPORT) {
    rpmDisplay.layout = RpmLayout::TRADITIONAL;
  }
  else {
    rpmDisplay.layout = RpmLayout::SPORT;
  }
}};
auto toggleLowPower = PushButton{D5, [](){
  INFO("Toggle Low Power");
  if (rpmDisplay.dimBrightness != 0) {
    rpmDisplay.dimBrightness = 0;
  }
  else {
    rpmDisplay.dimBrightness = 1;
  }
  vehicle.setLowPowerMode(!vehicle.inLowPowerMode());
}};

auto sensors = std::array {
  SensorFunction { []() { nextSceneButton.update(); } },
  SensorFunction { []() { actionButton.update(); } },
  SensorFunction { []() { toggleLowPower.update(); } },
};
auto sensorManager = SensorManager { sensors };

auto connectToVehicleCmd = ConnectToVehicleCommand { &vehicle };

void setup() {
  DebugScreen::Start([](U8G2& u8g2){
    auto rpmStr = std::string("RPM: ") + std::to_string(vehicle.rpm());
    auto speedStr = std::string("MPH: ") + std::to_string(vehicle.speed());
    auto coolantStr = std::string("Temp: ") + std::to_string(vehicle.coolantTemp());
    auto fpsStr = std::string("FPS: ") + std::to_string(Clock::Fps());
    u8g2.drawStr(0, 20, rpmStr.c_str());
    u8g2.drawStr(0, 30, speedStr.c_str());
    u8g2.drawStr(0, 40, coolantStr.c_str());
    u8g2.drawStr(0, 50, fpsStr.c_str());
  });
  if (LED_COUNT == 12) {
    ring.setShift(1);
    rpmDisplay.yellowLineStart = 3500;
    rpmDisplay.redLineStart = 4500;
    rpmDisplay.limit = 5000;
    rpmDisplay.colorMode = RpmColorMode::SEGMENTED;
  }
  else if (LED_COUNT == 16) {
    ring.setShift(10);
    ring.reverse();
    rpmDisplay.yellowLineStart = 5500;
    rpmDisplay.redLineStart = 6500;
    rpmDisplay.limit = 7000;
  }
  log::init();
  AppBuilder::Create()
    .EnableOTA()
    .DebugOutputLED(&slice)
    .SetSceneManager(&sceneManager)
    .SetLEDManager(&ledManager)
    .SetSensorManager(&sensorManager)
    .Start();

  VehicleThread::Start(vehicle);
}

void loop() {
  auto t = EaseOutCubic(vehicle.speed() / 140.0f);
  trailingScene.params.speed = Duration::Milliseconds(LerpClamp(100, 4, t));
  DebugScreen::Display();
  App::Loop();
}