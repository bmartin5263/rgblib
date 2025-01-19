//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_NEOPIXELDRIVER_H
#define RGBLIB_NEOPIXELDRIVER_H

#include "Adafruit_NeoPixel.h"
#include "Driver.h"
#include "core/Types.h"

class NeopixelDriver : public Driver {
public:
  NeopixelDriver(u16 ledCount, i16 pinNumber, neoPixelType type);
  auto draw(LEDChain& chain) -> void override;

private:
  Adafruit_NeoPixel impl;

  static auto FloatToByte(float f, u8 range = 255) -> u8;
};


#endif //RGBLIB_NEOPIXELDRIVER_H
