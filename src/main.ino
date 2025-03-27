#include <thread>
#include "App.h"
#include "AppBuilder.h"
#include "sensor/PushButton.h"
#include "effect/Timer.h"
#include "user/RpmDisplay.h"
#include "user/ChainableScene.h"
#include "user/SceneCycle.h"
#include "user/SolidScene.h"
#include "user/TrailingScene.h"
#include "user/NeopixelLEDManager.h"

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

constexpr u16 LED_COUNT = 12;

// Output
auto ring = LEDCircuit<LED_COUNT>{D2};
auto slice = ring.slice(6);
auto ledManager = NeopixelLEDManager<LED_COUNT>{ring};

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
  .endBuffer = 4
};
auto trailingScene = TrailingScene{trailingSceneParameters};

auto scenes = std::array {
  static_cast<Scene*>(&rpmDisplay),
  static_cast<Scene*>(&solidScene),
  static_cast<Scene*>(&trailingScene)
};
auto sceneManager = SceneCycle {scenes, &trailingScene, 800};

// Input
auto nextSceneButton = PushButton{D4, [](){
  sceneManager.nextScene();
}};
auto actionButton = PushButton{D9, [](){
  if (rpmDisplay.dimBrightness != 0) {
    rpmDisplay.dimBrightness = 0;
  }
  else {
    rpmDisplay.dimBrightness = 1;
  }
}};
auto toggleLowPower = PushButton{D12, [](){
  vehicle.setLowPowerMode(!vehicle.inLowPowerMode());
}};

TimerHandle handle;
bool flag;

void setup() {
  AppBuilder::Create()
      .DebugOutputLED(&slice)
      .SetSceneManager(&sceneManager)
      .SetLEDManager(&ledManager)
      .Start();

  handle = Timer::SetInterval(Duration::Milliseconds(100), 100, [](){
    if (rpmDisplay.dimBrightness != 0) {
      rpmDisplay.dimBrightness = 0;
    }
    else {
      rpmDisplay.dimBrightness = 1;
    }
    flag = !flag;
  });
}

void loop() {
  nextSceneButton.update();
  actionButton.update();
  toggleLowPower.update();
  App::Loop();
}