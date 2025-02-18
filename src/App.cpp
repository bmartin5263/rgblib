//
// Created by Brandon on 1/5/25.
//

#include <Adafruit_NeoPixel.h>

#include "App.hpp"
#include "Scene.h"
#include "Clock.h"
#include "network/OTASupport.h"
#include "network/WebServer.h"

namespace rgb {

App::App(): scene(nullptr), nextScene(nullptr) {

}

auto App::init(Scene* scene) -> void {
  Log::Init();
  OTASupport::Start();
  WebServer::Start();
  Clock::Init(200);

  this->scene = scene;
  this->scene->setup();
}

auto App::loop() -> void {
  OTASupport::Update();
  Clock::StartTick();

  if (nextScene != nullptr) {
    performSceneSwitch();
    nextScene = nullptr;
  }

  update();
  draw();

  Clock::StopTick();
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
  Instance().init(&NullScene::Instance());
}

auto App::Init(Scene& scene) -> void {
  Instance().init(&scene);
}

auto App::Loop() -> void {
  Instance().loop();
}

auto App::SwitchScene(Scene& scene) -> void {
  Instance().switchScene(scene);
}

}

