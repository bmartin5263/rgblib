//
// Created by Brandon on 5/6/26.
//

#include "SPIArduino.h"

namespace rgb::priv {

auto SPIArduino::start() -> bool {
  if (!isStarted()) {
    ::SPI.begin(RGB_SPI_SCK, RGB_SPI_MISO, RGB_SPI_MOSI, RGB_SPI_CS);
  }
  return isStarted();
}

auto SPIArduino::stop() -> void {
  ::SPI.end();
}

auto SPIArduino::isStarted() const -> bool {
  return ::SPI.bus() != nullptr;
}

}

