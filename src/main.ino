#include <bitset>
#include "Timer.h"
#include "DebugScreen.h"
#include "user/IntroScene.h"
#include "user/DebugScene.h"
#include "IRReceiver.h"
#include "App.h"
#include "AppBuilder.h"
#include "VehicleThread.h"
#include "AppBuilder.h"
#include "Iterable.h"

using namespace rgb;

constexpr auto LED_COUNT = 12;

auto ring = LEDCircuit<LED_COUNT>{D5};
auto slice = ring.slice(3);

auto vehicle = Vehicle{};
auto introScene = IntroScene{ring};
auto debugScene = DebugScene{ring, vehicle};
auto scenes = std::array {
  static_cast<Scene*>(&debugScene),
  static_cast<Scene*>(&introScene)
};

auto irReceiver = IRReceiver{};
auto sensors = std::array {
  Runnable { []() {
    static auto lastVehicleUpdate = Timestamp{};
    if (Clock::Now().timeSince(lastVehicleUpdate) > config::VEHICLE_REFRESH_RATE) {
      vehicle.update();
      lastVehicleUpdate = Clock::Now();
    }
  }},
  Runnable { []() {
    irReceiver.update();
  }}
};

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
auto leds = std::array {
  static_cast<Drawable*>(&ring)
};

auto setup() -> void {
  log::init();

  irReceiver.button0.onPress([](){ App::NextScene(); });
  irReceiver.start(D3);

  DebugScreen::Start();
  AppBuilder::Create()
    .DebugOutputLED(&slice)
    .EnableIntroScene(introScene, Duration::Seconds(1))
    .SetScenes(scenes)
    .SetLEDs(leds)
    .SetSensors(sensors)
    .Start();

  VehicleThread::Start(vehicle);
}

auto loop() -> void {
  if (DebugScreen::ReadyForUpdate()) {
//    updateDisplay();
    DebugScreen::Display();
  }
  App::Loop();
}