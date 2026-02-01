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
  std::variant<uint, normal> variant;

  template<class Container>
  auto getUnits(const Container& container) -> uint {
    if (std::holds_alternative<uint>(variant)) {
      return std::get<uint>(variant);
    }
    else {
      // Round down result
      return static_cast<uint>(container.size() * std::get<normal>(variant));
    }
  }

  static constexpr auto Units(uint units) -> Length {
    return Length{units};
  }

  static constexpr auto Ratio(normal ratio) -> Length {
    return Length{ratio};
  }

  auto operator++() -> Length& {
    if (std::holds_alternative<uint>(variant)) {
      std::get<uint>(variant) += 1;
    } else {
      std::get<normal>(variant) += 0.1f;
    }
    return *this;
  }

  auto operator++(int) -> Length {
    auto tmp = *this;
    ++(*this);
    return tmp;
  }

  auto operator--() -> Length& {
    if (std::holds_alternative<uint>(variant)) {
      auto& val = std::get<uint>(variant);
      if (val > 0) {
        val -= 1;
      }
    } else {
      auto& val = std::get<normal>(variant);
      if (val > 0.0f) {
        val -= 0.1f;
      }
    }
    return *this;
  }

  auto operator--(int) -> Length {
    auto tmp = *this;
    --(*this);
    return tmp;
  }
};

}

#endif //RGBLIB_LENGTH_H
