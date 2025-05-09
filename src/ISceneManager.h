//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_ISCENEMANAGER_H
#define RGBLIB_ISCENEMANAGER_H

namespace rgb {

class Scene;
class ISceneManager {
public:
  virtual auto start() -> Scene& = 0;
  virtual ~ISceneManager() = default;

  ISceneManager() = default;
  ISceneManager(const ISceneManager& rhs) = default;
  ISceneManager(ISceneManager&& rhs) noexcept = default;
  ISceneManager& operator=(const ISceneManager& rhs) = default;
  ISceneManager& operator=(ISceneManager&& rhs) noexcept = default;

};

}


#endif //RGBLIB_ISCENEMANAGER_H
