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

auto AppBuilder::SetSceneManager(ISceneManager* sceneManager) -> self {
  this->mSceneManager = sceneManager;
  return *this;
}

auto AppBuilder::SetLEDManager(ILEDManager* ledManager) -> self {
  this->mLedManager = ledManager;
  return *this;
}

auto AppBuilder::EnableOTA() -> self {
  mEnabledOTA = true;
  return *this;
}

auto AppBuilder::Start() -> void {
  App::Configure(*this);
  App::Start();
}

auto AppBuilder::SetSensorManager(ISensorManager* sensorManager) -> AppBuilder& {
  mSensorManager = sensorManager;
  return *this;
}


}