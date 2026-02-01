//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_GPIO_H
#define RGBLIB_GPIO_H

#include "priv/GPIOImpl.h"
#include "Types.h"
#include "Pin.h"

namespace rgb {

class GPIO {
public:
  static auto ActivatePin(PinNumber pin, PinMode mode) -> void;
  static auto ReadPin(PinNumber pin) -> int;

private:
  static auto Implementation() -> priv::GPIOImpl&;
  priv::GPIOImpl impl;
};

auto GPIO::Implementation() -> priv::GPIOImpl& {
  static GPIO instance;
  return instance.impl;
}

auto GPIO::ActivatePin(PinNumber pin, PinMode mode) -> void {
  Implementation().activatePin(pin, mode);
}

auto GPIO::ReadPin(rgb::PinNumber pin) -> int {
  return Implementation().readPin(pin);
}

}


#endif //RGBLIB_GPIO_H
