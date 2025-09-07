//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_APP_H
#define RGBLIB_APP_H

#include "Iterable.h"
#include "Func.h"
#include "TimerHandle.h"

namespace rgb {

class AppBuilder;
class Scene;
class LEDCircuit;
class App {
public:
  static auto Start() -> void;
  static auto Configure(const AppBuilder& appBuilder) -> void;
  static auto Loop() -> void;

  static auto NextScene() -> void { Instance().nextScene(); }
  static auto PrevScene() -> void { Instance().prevScene(); }
  static auto SwitchScene(Scene& scene) -> void;

  App(const App& rhs) = delete;
  App(App&& rhs) noexcept = delete;
  App& operator=(const App& rhs) = delete;
  App& operator=(App&& rhs) noexcept = delete;
private:
  App() = default;
  ~App() = default;

  static auto Instance() -> App&;

  auto start() -> void;
  auto configure(const AppBuilder& appBuilder) -> void;
  auto loop() -> void;
  auto switchScene(Scene& scene) -> void;
  auto nextScene() -> void;
  auto prevScene() -> void;
  auto checkForSceneSwitch() -> void;
  auto initializeStartingScene() -> void;
  auto checkForSleep() -> void;
  auto goToSleep() -> void;

  auto update() -> void;
  auto draw() -> void;

  Scene* scene;
  Scene* mNextScene;
  Scene* introScene{};
  Predicate activeCheck;
  Iterable<Scene*> scenes{};
  Iterable<LEDCircuit*> leds{};
  Iterable<Runnable> sensors{};
  TimerHandle introSceneTimer{};
  int currentScene{-1};
  Duration runIntroSceneFor;
  Duration activeCheckFrequency;
  Duration inactivityTimeout;
  Timestamp detectedInitialInactivityAt{};
  Timestamp lastActiveCheckAt{};
  bool started{};
  bool sleeping{};
};

}


#endif //RGBLIB_APP_H
