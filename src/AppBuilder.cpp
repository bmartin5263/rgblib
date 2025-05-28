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

auto AppBuilder::Start() -> void {
  App::Configure(*this);
  App::Start();
}

auto AppBuilder::SetLEDs(Iterable<Drawable*> leds) -> AppBuilder& {
  mLeds = leds;
  return *this;
}

auto AppBuilder::SetSensors(Iterable<Runnable> sensors) -> AppBuilder& {
  mSensors = sensors;
  return *this;
}

}