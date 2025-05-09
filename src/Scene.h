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

  Scene() = default;
  Scene(const Scene& rhs) = default;
  Scene(Scene&& rhs) noexcept = default;
  Scene& operator=(const Scene& rhs) = default;
  Scene& operator=(Scene&& rhs) noexcept = default;

private:

};

}

#endif //RGBLIB_SCENE_H
