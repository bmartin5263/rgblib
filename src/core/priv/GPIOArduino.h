//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_GPIOArduino_H
#define RGBLIB_GPIOArduino_H

#include <Arduino.h>
#include "GPIOBase.h"
#include "Assertions.h"

namespace rgb::priv {

class GPIOArduino : public GPIOBase {
public:
  static constexpr auto DEFAULT_PULL_UP = gpio_pullup_t::GPIO_PULLUP_ENABLE;
  static constexpr auto DEFAULT_PULL_DOWN = gpio_pulldown_t::GPIO_PULLDOWN_DISABLE;
  static constexpr auto DEFAULT_INTR_TYPE = gpio_int_type_t::GPIO_INTR_DISABLE;

  auto activatePin(PinNumber pin, PinMode mode) -> void;
  auto readPin(PinNumber pin) -> int;
private:
  static constexpr auto map(PinMode mode) -> int;
};

auto GPIOArduino::activatePin(PinNumber pin, PinMode mode) -> void {
  pinMode(pin.to<u8>(), map(mode));
}

auto GPIOArduino::readPin(rgb::PinNumber pin) -> int {
  return digitalRead(pin.to<u8>());
}

constexpr auto GPIOArduino::map(rgb::PinMode mode) -> int {
  switch (mode) {
    case PinMode::READ:
      return INPUT;
    case PinMode::WRITE:
      return OUTPUT;
  }
  ASSERT(false, "Invalid PinMode mapping");
}

}
#endif //RGBLIB_GPIOArduino_H
