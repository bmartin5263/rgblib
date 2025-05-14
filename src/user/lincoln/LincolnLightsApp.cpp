//
// Created by Brandon on 5/12/25.
//

#include "LincolnLightsApp.h"
#include "App.h"
#include "AppBuilder.h"
#include "VehicleThread.h"

using namespace rgb;

auto LincolnLightsApp::setup() -> void {
  DebugScreen::Start();
  rpmDisplay.yellowLineStart = 3000;
  rpmDisplay.redLineStart = 4000;
  rpmDisplay.limit = 4200;
  rpmDisplay.colorMode = RpmColorMode::SEGMENTED;
  rpmDisplay.glow = true;
  if (LED_COUNT == 8) {
    rpmDisplay.shape = RpmShape::LINE;
  }
  if (LED_COUNT == 12) {
    ring.setOffset(1);
  }
  else if (LED_COUNT == 16) {
    rpmDisplay.yellowLineStart = 5500;
    rpmDisplay.redLineStart = 6500;
    rpmDisplay.limit = 7200;
    ring.setOffset(3);
    ring.setReversed(true);
  }

  irReceiver.on0 = [](){ INFO("0"); };
  irReceiver.on1 = [](){ INFO("1"); };
  irReceiver.on2 = [](){ INFO("2"); };
  irReceiver.on3 = [](){ INFO("3"); };
  irReceiver.on4 = [](){ INFO("4"); };
  irReceiver.on5 = [](){ INFO("5"); };
  irReceiver.on6 = [](){ INFO("6"); };
  irReceiver.on7 = [](){ INFO("7"); };
  irReceiver.on8 = [](){ INFO("8"); };
  irReceiver.on9 = [](){ INFO("9"); };
  irReceiver.onUp = [](){ INFO("up"); };
  irReceiver.onRight = [](){ INFO("right"); };
  irReceiver.onDown = [](){ INFO("down"); };
  irReceiver.onLeft = [](){ INFO("left"); };
  irReceiver.onStar = [](){ INFO("*"); };
  irReceiver.onHash = [](){ INFO("#"); };
  irReceiver.onOk = [](){ INFO("ok"); };
  irReceiver.start(D3);

  log::init();
  AppBuilder::Create()
    .EnableOTA()
    .DebugOutputLED(&slice)
    .SetSceneManager(&sceneManager)
    .SetLEDManager(&ledManager)
    .SetSensorManager(&sensorManager)
    .Start();

//  VehicleThread::Start(vehicle);
}

auto LincolnLightsApp::updateDisplay() -> void {
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

auto LincolnLightsApp::loop() -> void {
  auto t = EaseOutCubic(vehicle.speed() / 140.0f);
  trailingScene.params.speed = Duration::Milliseconds(LerpClamp(100, 4, t));
  if (DebugScreen::ReadyForUpdate()) {
    updateDisplay();
    DebugScreen::Display();
  }
  App::Loop();
}
