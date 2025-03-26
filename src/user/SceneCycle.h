//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_SCENECYCLE_H
#define RGBLIB_SCENECYCLE_H

#include <array>
#include "SceneManager.h"
#include "Clock.h"
#include "Types.h"
#include "NullScene.h"
#include "sensor/PushButton.h"
#include "App.h"

namespace rgb {

template <uint N>
class SceneCycle : public SceneManager {
public:
  SceneCycle(
    std::array<Scene*, N>& scenes,
    Scene* introScene,
    milliseconds runIntroSceneFor
  ):
    scenes(scenes), introScene(introScene),runIntroSceneFor(runIntroSceneFor), introEndTime(0),
    currentScene(0), introSceneRunning(false)
  {

  }

  auto start() -> Scene& override {
    if (introScene != nullptr) {
      Log.infoLn("Intro Scene");
      currentScene = -1;
      introEndTime = Clock::Milli() + runIntroSceneFor;
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
    if (introSceneRunning && introSceneShouldEnd(Clock::Milli())) {
      Log.infoLn("Ending Intro Scene");
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
  milliseconds runIntroSceneFor;
  milliseconds introEndTime;
  int currentScene;
  bool introSceneRunning;

  auto introSceneShouldEnd(milliseconds now) -> bool {
    return now >= introEndTime;
  }
};


}

#endif //RGBLIB_SCENECYCLE_H
