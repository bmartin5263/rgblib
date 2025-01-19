//
// Created by Brandon on 1/5/25.
//

#include "NeopixelDriver.h"
#include "core/Assertions.h"
#include "led/LEDChain.h"

NeopixelDriver::NeopixelDriver(u16 ledCount, i16 pinNumber, neoPixelType type)
  : impl(ledCount, pinNumber, type) {
}

auto NeopixelDriver::draw(LEDChain& chain) -> void {
  for (u16 i = 0; i < chain.size(); ++i) {
    auto* color = chain.get(i);
    ASSERT(color != nullptr, "color is null");
    impl.setPixelColor(i, FloatToByte(color->g), FloatToByte(color->r), FloatToByte(color->b), FloatToByte(color->w));
  }
}

auto NeopixelDriver::FloatToByte(float f, u8 range) -> u8 {
  return ((u8)(f * range)) % (range + 1);
}