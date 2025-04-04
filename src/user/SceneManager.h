//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_SCENECYCLE_H
#define RGBLIB_SCENECYCLE_H

#include <array>
#include "ISceneManager.h"
#include "Clock.h"
#include "Types.h"
#include "NullScene.h"
#include "sensor/PushButton.h"
#include "App.h"

namespace rgb {

template <uint N>
class SceneManager : public ISceneManager {
public:
  SceneManager(
    std::array<Scene*, N>& scenes,
    Scene* introScene,
    Duration runIntroSceneFor
  ):
    scenes(scenes), introScene(introScene), runIntroSceneFor(runIntroSceneFor), introEndTime(0),
    currentScene(0), introSceneRunning(false)
  {

  }

  auto start() -> Scene& override {
    if (introScene != nullptr) {
      TRACE("Intro Scene");
      currentScene = -1;
      introEndTime = Clock::Micro() + runIntroSceneFor.value;
      introSceneRunning = true;
      return *introScene;
    }
    else if (N == 0) {
      return NullScene::Instance();
    }
    else {
      return *scenes[0];
    }
  }

  auto update() -> void override {
    if (introSceneRunning && introSceneShouldEnd(Clock::Micro())) {
      INFO("Ending Intro Scene");
      nextScene();
    }
  }

  auto nextScene() -> void {
    introSceneRunning = false;
    currentScene = (currentScene + 1) % N;
    App::SwitchScene(*scenes[currentScene]);
  }

  auto prevScene() -> void {
    introSceneRunning = false;
    currentScene = (currentScene > 0 ? currentScene : N) - 1;
    App::SwitchScene(*scenes[currentScene]);
  }

private:
  std::array<Scene*, N>& scenes;
  Scene* introScene;
  Duration runIntroSceneFor;
  microseconds introEndTime;
  int currentScene;
  bool introSceneRunning;

  auto introSceneShouldEnd(microseconds now) -> bool {
    return now >= introEndTime;
  }
};


}

#endif //RGBLIB_SCENECYCLE_H
