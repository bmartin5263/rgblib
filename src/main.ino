#include <thread>
#include <bitset>
#include "App.h"
#include "AppBuilder.h"
#include "sensor/PushButton.h"
#include "time/Timer.h"
#include "user/scene/RpmDisplay.h"
#include "user/SceneManager.h"
#include "user/scene/SolidScene.h"
#include "user/scene/TrailingScene.h"
#include "user/LEDManager.h"
#include "user/SensorManager.h"
#include "threading/VehicleThread.h"
#include "debug/DebugScreen.h"
#include "user/scene/IntroScene.h"
#include "user/scene/DebugScene.h"

using namespace rgb;

constexpr u16 LED_COUNT = 16;

// Output
auto ring = LEDCircuit<LED_COUNT>{D5};
auto slice = ring.slice(4);
auto ledManager = LEDManager<LED_COUNT>{ring};

// Scenes
auto vehicle = Vehicle{};
auto rpmDisplay = RpmDisplay{ring, vehicle};
auto solidScene = SolidScene{slice};
auto introScene = IntroScene{ring};
auto debugScene = DebugScene{ring, vehicle};
auto trailingScene = TrailingScene{ TrailingSceneParameters {
  .leds = &ring,
//  .colorGenerator = [](TrailingSceneColorGeneratorParameters params){
//    auto rpm = vehicle.rpm();
//    auto r = LerpClamp(0.0f, 1.0f, rpm, 4000.0f);
//    auto g = LerpClamp(1.0f, 0.0f, rpm, 4000.0f);
//    auto b = 0.0f;
//    auto brightness = LerpClamp(.02f, .03f, rpm, 4000.0f);
//    auto x = Pulse(params.now.asSeconds(), 1.f);
//    brightness += LerpClamp(0.f, .05f, x);
//
//    return Color {1.0f - x, 1.0f, 1.0f - x} * brightness;
//  },
//  .colorGenerator = [](TrailingSceneColorGeneratorParameters params){
//    auto r = LerpClamp(1.0f, .75f, vehicle.rpm() - 600, 3500.0f);
//    auto g = 0.0f;
//    auto b = LerpClamp(0.0f, .25f, vehicle.rpm() - 600, 3500.0f);
//    return Color { r, g, b } * .05f;
//  },
  .colorGenerator = [](TrailingSceneColorGeneratorParameters params){
    auto x = Pulse(params.now.asSeconds(), .5f);
    auto rgb = Color::HslToRgb(x) * .02f;
    return rgb;
  },
  .speed = Duration::Milliseconds(500),
  .shift = 6,
  .length = 6,
  .endBuffer = 4,
  .continuous = true
}};

auto scenes = std::array {
  static_cast<Scene*>(&rpmDisplay),
  static_cast<Scene*>(&trailingScene),
  static_cast<Scene*>(&debugScene)
};
auto sceneManager = SceneManager {scenes, &introScene, Duration::Minutes(60)};

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
  rpmDisplay.bright = !rpmDisplay.bright;
}};


auto sensors = std::array {
  SensorFunction { []() { nextSceneButton.update(); } },
  SensorFunction { []() { actionButton.update(); } },
  SensorFunction { []() { toggleLowPower.update(); } },
  SensorFunction { []() {
    static auto lastVehicleUpdate = Timestamp{};
    if (Clock::Now().timeSince(lastVehicleUpdate) > rgb::config::VEHICLE_REFRESH_RATE) {
      vehicle.update();
      lastVehicleUpdate = Clock::Now();
    }
  } },
};
auto sensorManager = SensorManager { sensors };

auto setup() -> void {
  DebugScreen::Start();
  rpmDisplay.yellowLineStart = 3000;
  rpmDisplay.redLineStart = 4000;
  rpmDisplay.limit = 4200;
  if (LED_COUNT == 12) {
    ring.setOffset(1);
    rpmDisplay.colorMode = RpmColorMode::SEGMENTED;
    rpmDisplay.glow = true;
  }
  else if (LED_COUNT == 16) {
    ring.setOffset(9);
    ring.setReversed(true);
    rpmDisplay.colorMode = RpmColorMode::SEGMENTED;
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

auto updateDisplay() -> void {
  auto fpsStr = "FPS: " + std::to_string(Clock::Fps())
                + "  MPH: " + std::to_string(static_cast<int>(vehicle.speed()));
  auto rpmStr = "RPM: " + std::to_string(static_cast<int>(vehicle.rpm()))
    + "  Coolant: " + std::to_string(static_cast<int>(vehicle.coolantTemp())) + "°F";
  auto fuelStr = "Fuel: " + std::to_string(static_cast<int>(vehicle.fuelLevel())) + "%"
    + "  Throttle: " + std::to_string(static_cast<int>(vehicle.throttlePosition() * 100)) + "%";
  DebugScreen::PrintLine(0, fpsStr);
  DebugScreen::PrintLine(1, rpmStr);
  DebugScreen::PrintLine(2, fuelStr);

  auto r = "Reversed: " + std::to_string(ring.isReversed());
  DebugScreen::PrintLine(3, r);
}

auto loop() -> void {
  auto t = EaseOutCubic(vehicle.speed() / 140.0f);
  trailingScene.params.speed = Duration::Milliseconds(LerpClamp(100, 4, t));
  if (DebugScreen::ReadyForUpdate()) {
    updateDisplay();
    DebugScreen::Display();
  }
  App::Loop();
}