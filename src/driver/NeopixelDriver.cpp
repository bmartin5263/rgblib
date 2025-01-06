//
// Created by Brandon on 1/5/25.
//

#include "NeopixelDriver.h"

NeopixelDriver::NeopixelDriver(u16 ledCount, i16 pinNumber, neoPixelType type)
  : impl(ledCount, pinNumber, type) {
}