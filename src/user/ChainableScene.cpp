//
// Created by Brandon on 3/18/25.
//

#include "App.h"
#include "ChainableScene.h"
#include "user/Grid.h"

namespace rgb {

ChainableScene::ChainableScene(
  PushButton& nextButton,
  PushButton& prevButton,
  Scene& theScene,
  Scene* nextScene,
  Scene* prevScene
): nextButton(&nextButton), prevButton(&prevButton), theScene(&theScene), nextScene(nextScene), prevScene(prevScene) {
}

auto ChainableScene::setup() -> void {
  theScene->setup();
}

auto ChainableScene::update() -> void {
  theScene->update();

  if (nextButton->update() == ButtonState::PRESS && nextScene != nullptr) {
    App::SwitchScene(*nextScene);
  }
  if (prevButton->update() == ButtonState::PRESS && prevScene != nullptr) {
    App::SwitchScene(*prevScene);
  }
}

auto ChainableScene::draw() -> void {
  theScene->draw();
}

auto ChainableScene::cleanup() -> void {
  theScene->cleanup();
}

}