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
#include "network/OTASupport.h"
#include "network/WebServer.h"
#include "effect/Timer.h"
#include "threading/ThreadPool.h"
#include "StartOTACommand.h"
#include "network/Wireless.h"

namespace rgb {

App::App(): scene(nullptr), nextScene(nullptr), sceneManager(nullptr), ledManager(nullptr), started(false) {

}

auto App::Configure(const AppBuilder& appBuilder) -> void {
  Instance().configure(appBuilder);
}

auto App::start() -> void {
  ASSERT(!started, "App has already started");

  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  ThreadPool::Start();
  Wifi::SetMode(WIFI_STA); // Wifi.mode() must be called on the main thread, else program crashes
  Wifi::Start();
  OTASupport::Start();
//  if (otaEnabled) {
//    ThreadPool::SubmitTask(StartOTACommand::Instance());
//  }

//  WebServer::Start();
  Clock::Init(config::FPS);

  this->scene = &sceneManager->start();
  this->scene->setup();
  this->started = true;
}

auto App::loop() -> void {
  Clock::StartTick();
  sensorManager->update();
  OTASupport::Update(); // todo - race condition
  Wifi::Update();

  ledManager->clear();
  Timer::ProcessTimers();

  sceneManager->update();
  checkForSceneSwitch();
  scene->update();

  Debug::Instance().draw();
  scene->draw();

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

