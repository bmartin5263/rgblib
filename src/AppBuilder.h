//
// Created by Brandon on 3/19/25.
//

#ifndef RGBLIB_APPBUILDER_H
#define RGBLIB_APPBUILDER_H

#include "Color.h"

namespace rgb {

class App;
class Scene;
class LEDChain;
class SceneManager;
class LEDManager;
struct Color;
class AppBuilder {
  using self = AppBuilder&;
public:
  auto DebugOutputLED(LEDChain* ledChain) -> self;
  auto SetSceneManager(SceneManager* sceneManager) -> self;
  auto SetLEDManager(LEDManager* ledManager) -> self;
  auto Start() -> void;

  static auto Create() -> AppBuilder { return {}; }

private:
  friend class App;

  LEDChain* mDebugOutputLED{nullptr};
  SceneManager* mSceneManager{nullptr};
  LEDManager* mLedManager{nullptr};
};

}

#endif //RGBLIB_APPBUILDER_H
