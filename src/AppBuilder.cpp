//
// Created by Brandon on 3/19/25.
//

#include "App.h"
#include "AppBuilder.h"

namespace rgb {

auto AppBuilder::DebugOutputLED(LEDChain* ledChain) -> self {
  this->mDebugOutputLED = ledChain;
  return *this;
}

auto AppBuilder::SetSceneManager(SceneManager* sceneManager) -> self {
  this->mSceneManager = sceneManager;
  return *this;
}

auto AppBuilder::SetLEDManager(LEDManager* ledManager) -> self {
  this->mLedManager = ledManager;
  return *this;
}

auto AppBuilder::Start() -> void {
  App::Configure(*this);
  App::Start();
}


}