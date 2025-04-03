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
#include "threading/ThreadPool.h"

using namespace rgb;

auto staticAssertions() -> void {
  static_assert(sizeof(i32) > sizeof(u16));
  static_assert(sizeof(i64) > sizeof(u32));
  static_assert(sizeof(int) == 4);
  static_assert(sizeof(int*) == 4);
  static_assert(sizeof(long) == 4);
  static_assert(sizeof(long long) == 8);
  static_assert(sizeof(float) == 4);
  static_assert(sizeof(double) == 8);
}

constexpr u16 LED_COUNT = 16;

// Output
auto ring = LEDCircuit<LED_COUNT>{D2};
auto slice = ring.slice(3);
auto ledManager = LEDManager<LED_COUNT>{ring};

// Scenes
auto vehicle = Vehicle{};
auto rpmDisplay = RpmDisplay{ring, vehicle};
auto solidScene = SolidScene{slice};

auto trailingSceneParameters = TrailingSceneParameters{
  .leds = &ring,
  .colorGenerator = [](auto params){
    return rgb::Color(
      0.f,
      rgb::ByteToFloat(params.relativePosition),
      0.f
    );
  },
  .speed = 8,
  .shift = 6,
  .length = LED_COUNT / 2,
  .endBuffer = 4,
  .continuous = true
};
auto trailingScene = TrailingScene{trailingSceneParameters};

auto scenes = std::array {
  static_cast<Scene*>(&trailingScene),
//  static_cast<Scene*>(&rpmDisplay),
//  static_cast<Scene*>(&solidScene)
};
auto sceneManager = SceneManager {scenes, nullptr, 0};

// Input
auto nextSceneButton = PushButton{D4, [](){
  sceneManager.nextScene();
}};
auto actionButton = PushButton{D6, [](){
  if (rpmDisplay.dimBrightness != 0) {
    rpmDisplay.dimBrightness = 0;
  }
  else {
    rpmDisplay.dimBrightness = 1;
  }
  if (rpmDisplay.layout == RpmLayout::SPORT) {
    rpmDisplay.layout = RpmLayout::TRADITIONAL;
  }
  else {
    rpmDisplay.layout = RpmLayout::SPORT;
  }
}};
auto toggleLowPower = PushButton{D9, [](){
  if (rpmDisplay.layout == RpmLayout::SPORT) {
    rpmDisplay.layout = RpmLayout::TRADITIONAL;
  }
  else {
    rpmDisplay.layout = RpmLayout::SPORT;
  }
}};

auto sensors = std::array<SensorFunction, 0>{
//  SensorFunction { []() { nextSceneButton.update(); } },
//  SensorFunction { []() { actionButton.update(); } },
//  SensorFunction { []() { toggleLowPower.update(); } },
};
auto sensorManager = SensorManager { sensors };

auto connectToVehicleCmd = ConnectToVehicleCommand { &vehicle };

void setup() {
  if (LED_COUNT == 12) {
    ring.setShift(2);
  }
  else if (LED_COUNT == 16) {
    ring.setShift(10);
    ring.reverse();
  }
  log::init();
//  delay(3000);
//  ThreadPool::Start();
//  ThreadPool::SubmitTask(connectToVehicleCmd);
  connectToVehicleCmd.execute();
  AppBuilder::Create()
      .EnableOTA()
      .DebugOutputLED(&slice)
      .SetSceneManager(&sceneManager)
      .SetLEDManager(&ledManager)
      .SetSensorManager(&sensorManager)
      .Start();
}

void loop() {
  vehicle.update();
  App::Loop();
}