//
// Created by Brandon on 5/6/26.
//

#ifndef RGBLIB_SPI_H
#define RGBLIB_SPI_H

#if RGB_ARDUINO_ESP32

#include "SPIImpl.h"

namespace rgb {

class SPI {
public:
  static auto Start() -> bool;
  static auto Stop() -> void;
  static auto IsStarted() -> bool;

  static constexpr auto CSPin() -> PinNumber { return priv::SPIImpl::csPin(); }
  static constexpr auto MISOPin() -> PinNumber { return priv::SPIImpl::misoPin(); }
  static constexpr auto MOSIPin() -> PinNumber { return priv::SPIImpl::mosiPin(); }
  static constexpr auto SCKPin() -> PinNumber { return priv::SPIImpl::sckPin(); }

private:
  static auto Implementation() -> priv::SPIImpl&;
  priv::SPIImpl impl;
};

}

#endif //defined(RGB_ARDUINO_ESP32)

#endif //RGBLIB_SPI_H
