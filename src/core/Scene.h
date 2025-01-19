//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_SCENE_H
#define RGBLIB_SCENE_H

class Scene {
public:
  auto doSetup() -> void;
  auto doUpdate() -> void;
  auto doDraw() -> void;
  auto doCleanup() -> void;

  virtual auto setup() -> void = 0;
  virtual auto update() -> void = 0;
  virtual auto draw() -> void = 0;
  virtual auto cleanup() -> void;

  virtual ~Scene() = default;

private:

};


#endif //RGBLIB_SCENE_H
