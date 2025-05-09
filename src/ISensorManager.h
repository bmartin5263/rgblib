//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_SCENEMANAGER_H
#define RGBLIB_SCENEMANAGER_H

namespace rgb {

class Scene;
class ISensorManager {
public:
  virtual auto update() -> void = 0;
  ISensorManager() = default;
  ISensorManager(const ISensorManager& rhs) = default;
  ISensorManager(ISensorManager&& rhs) noexcept = default;
  ISensorManager& operator=(const ISensorManager& rhs) = default;
  ISensorManager& operator=(ISensorManager&& rhs) noexcept = default;
  virtual ~ISensorManager() = default;

};

}


#endif //RGBLIB_SCENEMANAGER_H
