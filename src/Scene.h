//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_SCENE_H
#define RGBLIB_SCENE_H

#include "Log.h"

namespace rgb {
class Scene {
public:
  auto doSetup() -> void;
  auto doUpdate() -> void;
  auto doDraw() -> void;
  auto doCleanup() -> void;

  virtual auto setup() -> void {};
  virtual auto update() -> void = 0;
  virtual auto draw() -> void = 0;
  virtual auto cleanup() -> void {};

  virtual ~Scene() = default;

private:

};

class NullScene : public Scene {
public:
  auto update() -> void override {}
  auto draw() -> void override {}

  static NullScene& Instance();
};
}

#endif //RGBLIB_SCENE_H
