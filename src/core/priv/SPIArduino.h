//
// Created by Brandon on 5/6/26.
//

#ifndef RGBLIB_SPIArduino_H
#define RGBLIB_SPIArduino_H

#include <Arduino.h>
#include <SPI.h>
#include "Pin.h"
#include "SPIBase.h"

#ifndef RGB_SPI_SCK
#define RGB_SPI_SCK A2
#endif

#ifndef RGB_SPI_MISO
#define RGB_SPI_MISO A0
#endif

#ifndef RGB_SPI_MOSI
#define RGB_SPI_MOSI A1
#endif

#ifndef RGB_SPI_CS
#define RGB_SPI_CS A3
#endif

namespace rgb::priv {

class SPIArduino : public SPIBase {
public:
  auto start() -> bool;
  auto stop() -> void;
  auto isStarted() const -> bool;

  static constexpr auto csPin() -> PinNumber { return PinNumber{RGB_SPI_CS}; }
  static constexpr auto misoPin() -> PinNumber { return PinNumber{RGB_SPI_MISO}; }
  static constexpr auto mosiPin() -> PinNumber { return PinNumber{RGB_SPI_MOSI}; }
  static constexpr auto sckPin() -> PinNumber { return PinNumber{RGB_SPI_SCK}; }
};

}
#endif //RGBLIB_SPIArduino_H
