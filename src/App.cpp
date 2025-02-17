//
// Created by Brandon on 1/5/25.
//

#include <Adafruit_NeoPixel.h>

#include "App.hpp"
#include "Scene.h"
#include "Clock.h"
#include "Debug.h"
#include "OTASupport.h"

Adafruit_NeoPixel circuit(16, D5, NEO_GRBW + NEO_KHZ800);
int counter = 0;

App::App(): scene(nullptr), nextScene(nullptr) {

}

auto App::init() -> void {
  Log::Init();
  OTASupport::Start();
  Clock::Init(200);
  this->scene = nullptr;

  circuit.begin();
  circuit.setBrightness(10);
}

auto App::init(Scene& scene) -> void {
  Log::Init();
  OTASupport::Start();
  Clock::Init(200);
  this->scene = &scene;
}

auto App::loop() -> void {
  OTASupport::Update();
  Clock::StartTick();
//
//  if (nextScene != nullptr) {
//    performSceneSwitch();
//    nextScene = nullptr;
//  }

  if (scene != nullptr) {
    update();
    draw();
  }

  circuit.clear();
  for (int i = 0; i < 16; ++i) {
    circuit.setPixelColor(i, 0, 0, 0, 0);
  }

  for (int i = 0; i < 6; ++i) {
    auto c = (counter + i) % 16;
    circuit.setPixelColor(c, 0, 255, 0, 0);
  }
  counter = (counter + 1) % 16;

  circuit.show();
  delay(100);

//  Clock::StopTick();
}

auto App::update() -> void {
  scene->update();
//  Debug::Instance().update();
}

auto App::draw() -> void {
  scene->draw();
}

auto App::switchScene(Scene& scene) -> void {
  this->nextScene = &scene;
}

auto App::performSceneSwitch() -> void {
  this->scene->cleanup();
  this->scene = nextScene;
  this->scene->setup();
}

auto App::Instance() -> App& {
  static App instance;
  return instance;
}

auto App::Init() -> void {
  Instance().init();
}

auto App::Init(Scene& scene) -> void {
  Instance().init(scene);
}

auto App::Loop() -> void {
  Instance().loop();
}

auto App::SwitchScene(Scene& scene) -> void {
  Instance().switchScene(scene);
}

