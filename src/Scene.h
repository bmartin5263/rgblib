//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_SCENE_H
#define RGBLIB_SCENE_H

#include "Log.h"

namespace rgb {
class Scene {
public:
  virtual auto update() -> void = 0;
  virtual auto draw() -> void = 0;
  virtual auto setup() -> void {};
  virtual auto cleanup() -> void {};

  virtual ~Scene() = default;

private:

};

}

#endif //RGBLIB_SCENE_H
