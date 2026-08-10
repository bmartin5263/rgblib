//
// Created by Brandon on 7/26/26.
//

#include "RgbSPI.h"

namespace rgb {

auto SPI::Implementation() -> priv::SPIImpl& {
  static SPI instance;
  return instance.impl;
}

auto SPI::Start() -> bool {
  return Implementation().start();
}

auto SPI::Stop() -> void {
  Implementation().stop();
}

auto SPI::IsStarted() -> bool {
  return Implementation().isStarted();
}

}
