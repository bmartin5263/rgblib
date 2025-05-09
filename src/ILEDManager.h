//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_ILEDMANAGER_H
#define RGBLIB_ILEDMANAGER_H

namespace rgb {

class ILEDManager {
public:
  virtual auto clear() -> void = 0;
  virtual auto display() -> void = 0;
  ILEDManager() = default;
  ILEDManager(const ILEDManager& rhs) = default;
  ILEDManager(ILEDManager&& rhs) noexcept = default;
  ILEDManager& operator=(const ILEDManager& rhs) = default;
  ILEDManager& operator=(ILEDManager&& rhs) noexcept = default;
  virtual ~ILEDManager() = default;

};

}


#endif //RGBLIB_ILEDMANAGER_H
