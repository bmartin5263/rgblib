//
// Created by Brandon on 1/5/25.
//

#include <Adafruit_NeoPixel.h>

#include "App.h"
#include "Scene.h"
#include "Clock.h"
#include "network/OTASupport.h"
#include "network/WebServer.h"

namespace rgb {

App::App(): scene(nullptr), nextScene(nullptr) {

}

auto App::init(Scene* scene) -> void {
  Log.init();
  OTASupport::Start();
  WebServer::Start();
  Clock::Init(config::FPS);

  this->scene = scene;
  this->scene->setup();
}

auto App::loop() -> void {
  OTASupport::Update();
  Clock::StartTick();

  checkForSceneSwitch();
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

