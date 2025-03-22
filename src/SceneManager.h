//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_SCENEMANAGER_H
#define RGBLIB_SCENEMANAGER_H

namespace rgb {

class Scene;
class SceneManager {
public:
  virtual auto update() -> void = 0;
  virtual auto start() -> Scene& = 0;
  virtual ~SceneManager() = default;

};

}


#endif //RGBLIB_SCENEMANAGER_H
