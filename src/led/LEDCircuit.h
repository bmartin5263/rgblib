//
// Created by Brandon on 5/26/25.
//

#ifndef RGBLIB_LEDLIST_H
#define RGBLIB_LEDLIST_H

namespace rgb {

class LEDCircuit {
public:
  LEDCircuit() = default;
  LEDCircuit(const LEDCircuit& rhs) = default;
  LEDCircuit(LEDCircuit&& rhs) noexcept = default;
  LEDCircuit& operator=(const LEDCircuit& rhs) = default;
  LEDCircuit& operator=(LEDCircuit&& rhs) noexcept = default;
  virtual ~LEDCircuit() = default;

  virtual auto reset() -> void = 0;
  virtual auto display() -> void = 0;
};


}
#endif //RGBLIB_LEDLIST_H
