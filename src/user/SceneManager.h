//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_SCENECYCLE_H
#define RGBLIB_SCENECYCLE_H

#include <array>
#include "ISceneManager.h"
#include "Clock.h"
#include "Timer.h"
#include "Types.h"
#include "NullScene.h"
#include "PushButton.h"
#include "App.h"

template <uint N>
class SceneManager : public rgb::ISceneManager {
public:
  SceneManager(
    std::array<rgb::Scene*, N>& scenes,
    rgb::Scene* introScene,
    rgb::Duration runIntroSceneFor
  ):
    scenes(scenes), introScene(introScene), runIntroSceneFor(runIntroSceneFor), introEndTime(0),
    currentScene(0), introSceneTimer(), introSceneRunning(false)
  {

  }

  auto start() -> rgb::Scene& override {
    if (introScene != nullptr) {
      currentScene = -1;
      INFO("Starting");
      introSceneTimer = rgb::Timer::SetTimeout(runIntroSceneFor, [&](){
        INFO("Ending Intro Scene");
        nextScene();
      });
      return *introScene;
    }
    else if (N == 0) {
      return rgb::NullScene::Instance();
    }
    else {
      return *scenes[0];
    }
  }

  auto nextScene() -> void {
    INFO("---> Next Scene --->");
    introSceneTimer.reset();
    currentScene = (currentScene + 1) % N;
    rgb::App::SwitchScene(*scenes[currentScene]);
  }

  auto prevScene() -> void {
    introSceneRunning = false;
    currentScene = (currentScene > 0 ? currentScene : N) - 1;
    rgb::App::SwitchScene(*scenes[currentScene]);
  }

private:
  std::array<rgb::Scene*, N>& scenes;
  rgb::Scene* introScene;
  rgb::Duration runIntroSceneFor;
  rgb::Timestamp introEndTime;
  int currentScene;
  rgb::TimerHandle introSceneTimer;
  bool introSceneRunning;
};


#endif //RGBLIB_SCENECYCLE_H
