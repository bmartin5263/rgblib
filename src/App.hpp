//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_APP_H
#define RGBLIB_APP_H

class Scene;
class App {
public:
  App(const App&) = delete;
  App(App&&) noexcept = delete;

  auto operator=(const App& other) -> App& = delete;
  auto operator=(App&& other) noexcept -> App& = delete;

  static auto Init(Scene& scene) -> void;
  static auto Loop() -> void;
  static auto SwitchScene(Scene& scene) -> void;

private:
  App();
  ~App() = default;

  static auto Instance() -> App&;

  auto init(Scene& scene) -> void;
  auto loop() -> void;
  auto switchScene(Scene& scene) -> void;
  auto performSceneSwitch() -> void;
  auto update() -> void;
  auto draw() -> void;

  Scene* scene;
  Scene* nextScene;
};


#endif //RGBLIB_APP_H
