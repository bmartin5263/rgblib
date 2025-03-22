//
// Created by Brandon on 3/18/25.
//

#ifndef RGBLIB_ABSTRACTSCENE_H
#define RGBLIB_ABSTRACTSCENE_H

#include "Scene.h"

namespace rgb {

class PushButton;
class ChainableScene : public Scene {
public:
  ChainableScene(
    PushButton& nextButton,
    PushButton& prevButton,
    Scene& theScene,
    Scene* nextScene = nullptr,
    Scene* prevScene = nullptr
  );

  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;
  auto cleanup() -> void override;

  auto setNextScene(ChainableScene* next);
  auto setPreviousScene(ChainableScene* prev);

private:
  PushButton* nextButton;
  PushButton* prevButton;
  Scene* theScene;
  Scene* nextScene;
  Scene* prevScene;

};

}

#endif //RGBLIB_ABSTRACTSCENE_H
