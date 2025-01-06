//
// Created by Brandon on 1/5/25.
//

#include "App.hpp"
#include "Scene.h"
#include "Clock.h"
#include "Util.h"
#include "Debug.h"

App::App(): scene(nullptr), nextScene(nullptr) {

}

auto App::init(Scene& scene) -> void {
  Clock::Instance().initialize(200);
}

auto App::loop() -> void {
  auto clock = Clock::Instance();
  clock.startTick();

  if (nextScene != nullptr) {
    performSceneSwitch();
    nextScene = nullptr;
  }

  update();
  draw();

  clock.stopTick();
}

auto App::update() -> void {
  scene->update();
  Debug::Instance().update();
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

auto App::Init(Scene& scene) -> void {
  Instance().init(scene);
}

auto App::Loop() -> void {
  Instance().loop();
}

auto App::SwitchScene(Scene& scene) -> void {
  Instance().switchScene(scene);
}
