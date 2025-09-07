//
// Created by Brandon on 3/19/25.
//

#include "App.h"
#include "AppBuilder.h"

#include <utility>

namespace rgb {

auto AppBuilder::DebugOutputLED(PixelList* pixels) -> self {
  this->mDebugOutputLED = pixels;
  return *this;
}

auto AppBuilder::Start() const -> void {
  App::Configure(*this);
  App::Start();
}

auto AppBuilder::SetLEDs(Iterable<LEDCircuit*> leds) -> AppBuilder& {
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

auto AppBuilder::SetActiveCheck(Duration frequency, Predicate activeCheck) -> self {
  mActiveCheckFrequency = frequency;
  mActiveCheck = std::move(activeCheck);
  return *this;
}

auto AppBuilder::EnableIntroScene(rgb::Scene& introScene, rgb::Duration expirationTime) -> self {
  mIntroScene = &introScene;
  mRunIntroSceneFor = expirationTime;
  return *this;
}

auto AppBuilder::SetInactivityTimeout(Duration timeout) -> AppBuilder& {
  mInactivityTimeout = timeout;
  return *this;
}

}