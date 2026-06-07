//
// Created by Brandon on 5/26/25.
//

#ifndef RGBLIB_LEDCIRCUIT_H
#define RGBLIB_LEDCIRCUIT_H

namespace rgb {

class LEDDevice {
public:
  LEDDevice() = default;
  virtual ~LEDDevice() = default;

  virtual auto start() -> void = 0;
  virtual auto reset() -> void = 0;
  virtual auto display() -> void = 0;

protected:
  LEDDevice(const LEDDevice& rhs) = default;
  LEDDevice(LEDDevice&& rhs) noexcept = default;
  LEDDevice& operator=(const LEDDevice& rhs) = default;
  LEDDevice& operator=(LEDDevice&& rhs) noexcept = default;
};


}
#endif //RGBLIB_LEDCIRCUIT_H
