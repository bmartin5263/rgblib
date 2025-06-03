//
// Created by Brandon on 3/19/25.
//

#include "App.h"
#include "AppBuilder.h"

namespace rgb {

auto AppBuilder::DebugOutputLED(PixelList* pixels) -> self {
  this->mDebugOutputLED = pixels;
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

auto AppBuilder::SetLEDs(Iterable<LEDList*> leds) -> AppBuilder& {
  mLeds = leds;
  return *this;
}

auto AppBuilder::SetSensors(Iterable<Runnable> sensors) -> AppBuilder& {
  mSensors = sensors;
  return *this;
}

auto AppBuilder::SetScenes(Iterable<rgb::Scene*> scenes) -> self {
  mScenes = scenes;
  return *this;
}

auto AppBuilder::EnableIntroScene(rgb::Scene& introScene, rgb::Duration expirationTime) -> self {
  mIntroScene = &introScene;
  mRunIntroSceneFor = expirationTime;
  return *this;
}

}