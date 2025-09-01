//
// Created by Brandon on 8/17/25.
//

#ifndef RGBLIB_LENGTH_H
#define RGBLIB_LENGTH_H

#include <variant>
#include "Types.h"

namespace rgb {

class Length {
public:
  std::variant<u32, normal> variant;

  static constexpr auto Units(u32 units) -> Length {
    return Length{units};
  }

  static constexpr auto Ratio(normal ratio) -> Length {
    return Length{ratio};
  }
};

}

#endif //RGBLIB_LENGTH_H
