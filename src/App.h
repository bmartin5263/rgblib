//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_APP_H
#define RGBLIB_APP_H

namespace rgb {

class AppBuilder;
class Scene;
class ISceneManager;
class ILEDManager;
class ISensorManager;
class App {
public:
  App(const App&) = delete;
  App(App&&) noexcept = delete;

  auto operator=(const App& other) -> App& = delete;
  auto operator=(App&& other) noexcept -> App& = delete;

  static auto Start() -> void;
  static auto Configure(const AppBuilder& appBuilder) -> void;
  static auto Loop() -> void;

  static auto SwitchScene(Scene& scene) -> void;

private:
  App() = default;
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
  ILEDManager* ledManager;
  ISensorManager* sensorManager{};
  bool started;
  bool otaEnabled;
};

}


#endif //RGBLIB_APP_H
