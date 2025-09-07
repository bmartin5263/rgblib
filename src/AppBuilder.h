//
// Created by Brandon on 3/19/25.
//

#ifndef RGBLIB_APPBUILDER_H
#define RGBLIB_APPBUILDER_H

#include "Color.h"
#include "Func.h"
#include "Iterable.h"

namespace rgb {

template <typename T>
struct Iterable;
class App;
class Scene;
class PixelList;
class LEDCircuit;
struct Color;
class AppBuilder {
  using self = AppBuilder&;
public:
  auto DebugOutputLED(PixelList* pixels) -> self;
  auto SetSensors(Iterable<Runnable> sensors) -> self;
  auto SetScenes(Iterable<Scene*> scenes) -> self;
  auto SetLEDs(Iterable<LEDCircuit*> scenes) -> self;
  auto EnableIntroScene(Scene& scene, Duration expirationTime) -> self;
  auto SetActiveCheck(Duration frequency, Predicate activeCheck) -> self;
  auto SetInactivityTimeout(Duration timeout) -> self;

  auto Start() const -> void;
  static auto Create() -> AppBuilder { return {}; }

private:
  friend class App;

  PixelList* mDebugOutputLED{nullptr};
  Iterable<LEDCircuit*> mLeds{};
  Iterable<Scene*> mScenes{};
  Scene* mIntroScene{nullptr};
  Predicate mActiveCheck{[](){ return true; }};
  Duration mActiveCheckFrequency{Duration::Minutes(1)};
  Duration mRunIntroSceneFor{Duration::Seconds(1)};
  Duration mInactivityTimeout{Duration::Seconds(10)};
  Iterable<Runnable> mSensors{};
};

}

#endif //RGBLIB_APPBUILDER_H
