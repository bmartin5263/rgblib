//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_PIN_H
#define RGBLIB_PIN_H

#include "Types.h"
#include "Handle.h"

namespace rgb {

enum class PinMode {
  READ,
  WRITE
};

struct PinNumber {
  constexpr explicit PinNumber(uint value): value(value) {}

  template<class T>
  constexpr auto to() const -> T {
    return static_cast<T>(value);
  }

  uint value;
};

struct TurnOffPin {
  auto operator()(PinNumber number) -> void;
};

using Pin = Handle<PinNumber, TurnOffPin>;

}

#endif //RGBLIB_PIN_H
