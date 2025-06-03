//
// Created by Brandon on 5/26/25.
//

#ifndef RGBLIB_LEDLIST_H
#define RGBLIB_LEDLIST_H

namespace rgb {

class LEDList {
public:
  LEDList() = default;
  LEDList(const LEDList& rhs) = default;
  LEDList(LEDList&& rhs) noexcept = default;
  LEDList& operator=(const LEDList& rhs) = default;
  LEDList& operator=(LEDList&& rhs) noexcept = default;
  virtual ~LEDList() = default;

  virtual auto reset() -> void = 0;
  virtual auto display() -> void = 0;
};


}
#endif //RGBLIB_LEDLIST_H
