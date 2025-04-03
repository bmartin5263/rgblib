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
class ISceneManager;
class ILEDManager;
class ISensorManager;
struct Color;
class AppBuilder {
  using self = AppBuilder&;
public:
  auto DebugOutputLED(LEDChain* ledChain) -> self;
  auto SetSceneManager(ISceneManager* sceneManager) -> self;
  auto SetLEDManager(ILEDManager* ledManager) -> self;
  auto SetSensorManager(ISensorManager* sensorManager) -> self;
  auto EnableOTA() -> self;
  auto Start() -> void;

  static auto Create() -> AppBuilder { return {}; }

private:
  friend class App;

  LEDChain* mDebugOutputLED{nullptr};
  ISceneManager* mSceneManager{nullptr};
  ILEDManager* mLedManager{nullptr};
  ISensorManager* mSensorManager{nullptr};
  bool mEnabledOTA{false};
};

}

#endif //RGBLIB_APPBUILDER_H
