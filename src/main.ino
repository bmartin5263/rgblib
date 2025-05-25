#include <bitset>
#include "Timer.h"
#include "SceneManager.h"
#include "LEDManager.h"
#include "SensorManager.h"
#include "DebugScreen.h"
#include "user/IntroScene.h"
#include "user/DebugScene.h"
#include "IRReceiver.h"
#include "App.h"
#include "AppBuilder.h"
#include "VehicleThread.h"
#include "AppBuilder.h"

using namespace rgb;

constexpr auto LED_COUNT = 12;

auto ring = LEDCircuit<LED_COUNT>{D5};
auto slice = ring.slice(3);
auto ledManager = LEDManager<LED_COUNT>{ring};

auto vehicle = Vehicle{};
auto introScene = IntroScene{ring};
auto debugScene = DebugScene{ring, vehicle};
auto scenes = std::array {
  static_cast<Scene*>(&debugScene)
};
auto sceneManager = SceneManager<1>{scenes, &introScene, Duration::Seconds(2)};

auto irReceiver = IRReceiver{};
auto sensors = std::array {
  SensorFunction { []() {
    static auto lastVehicleUpdate = Timestamp{};
    if (Clock::Now().timeSince(lastVehicleUpdate) > config::VEHICLE_REFRESH_RATE) {
      vehicle.update();
      lastVehicleUpdate = Clock::Now();
    }
  }},
  SensorFunction { []() {
    irReceiver.update();
  }}
};
auto sensorManager = SensorManager<2>{ sensors };

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

auto setup() -> void {
  irReceiver.button0.onPress([](){ INFO("button 0"); });
  irReceiver.button1.onPress([](){ INFO("button 1"); });
  irReceiver.button2.onPress([](){ INFO("button 2"); });
  irReceiver.button3.onPress([](){ INFO("button 3"); });
  irReceiver.button4.onPress([](){ INFO("button 4"); });
  irReceiver.button5.onPress([](){ INFO("button 5"); });
  irReceiver.button6.onPress([](){ INFO("button 6"); });
  irReceiver.button7.onPress([](){ INFO("button 7"); });
  irReceiver.button8.onPress([](){ INFO("button 8"); });
  irReceiver.button9.onPress([](){ INFO("button 9"); });
  irReceiver.start(D3);

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

auto loop() -> void {
  if (DebugScreen::ReadyForUpdate()) {
    updateDisplay();
    DebugScreen::Display();
  }
  App::Loop();
}