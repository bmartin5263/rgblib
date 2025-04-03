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
  virtual ~ISensorManager() = default;

};

}


#endif //RGBLIB_SCENEMANAGER_H
