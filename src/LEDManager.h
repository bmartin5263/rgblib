//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_LEDMANAGER_H
#define RGBLIB_LEDMANAGER_H

namespace rgb {

class LEDManager {
public:
  virtual auto clear() -> void = 0;
  virtual auto display() -> void = 0;
  virtual ~LEDManager() = default;

};

}


#endif //RGBLIB_LEDMANAGER_H
