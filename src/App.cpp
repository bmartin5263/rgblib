//
// Created by Brandon on 1/5/25.
//

#include <Adafruit_NeoPixel.h>

#include "App.h"
#include "AppBuilder.h"
#include "Scene.h"
#include "Clock.h"
#include "Assertions.h"
#include "OTASupport.h"
#include "WebServer.h"
#include "Timer.h"
#include "LEDCircuit.h"

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

  log::init();
  Clock::Start(config::FPS);
  if constexpr (Wifi::Enabled()) {
    Wifi::SetMode(WIFI_STA); // Wifi.mode() must be called on the main thread, else program crashes
    Wifi::Start();
    OTASupport::Start();
  }

  if (introScene != nullptr) {
    this->scene = introScene;
    this->introSceneTimer = rgb::Timer::SetTimeout(runIntroSceneFor, [&](){
      INFO("Ending Intro Scene");
      nextScene();
    });
  }
  else {
    this->scene = scenes[0];
  }

  this->scene->setup();
  this->started = true;
}

auto App::loop() -> void {
  Clock::StartTick();
  update();
  draw();
  Clock::StopTick();
}

auto App::update() -> void {
  for (auto& sensor : sensors) {
    sensor();
  }
  if constexpr (Wifi::Enabled()) {
    Wifi::Update();
  }
  if constexpr (OTASupport::Enabled()) {
    OTASupport::Update();
  }

  Timer::ProcessTimers();
  checkForSceneSwitch();
  scene->update();
}

auto App::draw() -> void {
  leds.forEach([](auto led){ led->reset();} );
  scene->draw();
  Debug::Draw();
  leds.forEach([](auto led){ led->display();} );
}

auto App::switchScene(Scene& scene) -> void {
  this->mNextScene = &scene;
}

auto App::checkForSceneSwitch() -> void {
  if (mNextScene != nullptr) {
    scene->cleanup();
    scene = mNextScene;
    scene->setup();
    mNextScene = nullptr;
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
  leds = appBuilder.mLeds;
  sensors = appBuilder.mSensors;
  scenes = appBuilder.mScenes;
  runIntroSceneFor = appBuilder.mRunIntroSceneFor;
  introScene = appBuilder.mIntroScene;
  Debug::SetDebugChain(appBuilder.mDebugOutputLED);
}


auto App::nextScene() -> void {
  INFO("---> Next Scene --->");
  introSceneTimer.cancel();
  currentScene = (currentScene + 1) % scenes.size();
  ASSERT(scenes[currentScene] != nullptr, "Null scene detected");
  switchScene(*scenes[currentScene]);
}

auto App::prevScene() -> void {
  INFO("<--- Previous Scene <---");
  introSceneTimer.cancel();
  currentScene = (currentScene > 0 ? currentScene : scenes.size()) - 1;
  ASSERT(scenes[currentScene] != nullptr, "Null scene detected");
  switchScene(*scenes[currentScene]);
}

}

