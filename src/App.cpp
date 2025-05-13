//
// Created by Brandon on 1/5/25.
//

#include <Adafruit_NeoPixel.h>

#include "App.h"
#include "AppBuilder.h"
#include "Scene.h"
#include "Clock.h"
#include "Assertions.h"
#include "ISceneManager.h"
#include "ILEDManager.h"
#include "ISensorManager.h"
#include "OTASupport.h"
#include "WebServer.h"
#include "Timer.h"

namespace rgb {

auto App::Configure(const AppBuilder& appBuilder) -> void {
  Instance().configure(appBuilder);
}

auto App::start() -> void {
  ASSERT(!started, "App has already started");

  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, HIGH);

  Clock::Start(config::FPS);
  if constexpr (Wifi::Enabled()) {
    Wifi::SetMode(WIFI_STA); // Wifi.mode() must be called on the main thread, else program crashes
    Wifi::Start();
    OTASupport::Start();
  }

  this->scene = &sceneManager->start();
  this->scene->setup();
  this->started = true;
}

auto App::loop() -> void {
  Clock::StartTick();
  sensorManager->update();
  if constexpr (Wifi::Enabled()) {
    Wifi::Update();
  }
  if constexpr (OTASupport::Enabled()) {
    OTASupport::Update();
  }

  Timer::ProcessTimers();

  checkForSceneSwitch();
  scene->update();

  ledManager->clear();
  scene->draw();
  Debug::Instance().draw();
  ledManager->display();

  Clock::StopTick();
}

auto App::switchScene(Scene& scene) -> void {
  this->nextScene = &scene;
}

auto App::checkForSceneSwitch() -> void {
  if (nextScene != nullptr) {
    scene->cleanup();
    scene = nextScene;
    scene->setup();
    nextScene = nullptr;
  }
}

auto App::Instance() -> App& {
  static App instance;
  return instance;
}

auto App::Start() -> void {
  Instance().start();
}

auto App::Loop() -> void {
  Instance().loop();
}

auto App::SwitchScene(Scene& scene) -> void {
  Instance().switchScene(scene);
}

auto App::configure(const AppBuilder& appBuilder) -> void {
  ASSERT(!started, "App has already started");
  sceneManager = appBuilder.mSceneManager;
  ledManager = appBuilder.mLedManager;
  sensorManager = appBuilder.mSensorManager;
  otaEnabled = appBuilder.mEnabledOTA;
  Debug::Instance().setDebugChain(appBuilder.mDebugOutputLED);
}

}

