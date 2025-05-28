//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_APP_H
#define RGBLIB_APP_H

#include "Iterable.h"
#include "Func.h"

namespace rgb {

class AppBuilder;
class Scene;
class ISceneManager;
class ILEDManager;
class ISensorManager;
class Drawable;
class App {
public:
  static auto Start() -> void;
  static auto Configure(const AppBuilder& appBuilder) -> void;
  static auto Loop() -> void;

  static auto SwitchScene(Scene& scene) -> void;

private:
  App() = default;
  App(const App& rhs) = delete;
  App(App&& rhs) noexcept = delete;
  App& operator=(const App& rhs) = delete;
  App& operator=(App&& rhs) noexcept = delete;
  ~App() = default;

  static auto Instance() -> App&;

  auto start() -> void;
  auto configure(const AppBuilder& appBuilder) -> void;

  auto loop() -> void;
  auto switchScene(Scene& scene) -> void;
  auto checkForSceneSwitch() -> void;

  Scene* scene;
  Scene* nextScene;
  ISceneManager* sceneManager;
  Iterable<Drawable*> leds{};
  Iterable<Runnable> sensors{};
  bool started;
};

}


#endif //RGBLIB_APP_H
