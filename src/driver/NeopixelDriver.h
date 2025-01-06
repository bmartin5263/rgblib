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

private:
  Adafruit_NeoPixel impl;

};


#endif //RGBLIB_NEOPIXELDRIVER_H
