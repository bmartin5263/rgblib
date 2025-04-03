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
  virtual ~ILEDManager() = default;

};

}


#endif //RGBLIB_ILEDMANAGER_H
