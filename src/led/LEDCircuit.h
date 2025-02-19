//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_LEDCIRCUIT_H
#define RGBLIB_LEDCIRCUIT_H

#include <Adafruit_NeoPixel.h>
#include "Types.h"
#include "Assertions.h"
#include "Color.h"
#include "LEDChain.h"
#include "LEDSlice.h"

namespace rgb {

template <u16 N>
class LEDCircuit : public LEDChain {
public:
  explicit LEDCircuit(pin_num pin, neoPixelType type = NEO_GRBW + NEO_KHZ800): data{}, impl(N, pin, type) {

  }

  auto start() -> void {
    impl.begin();
  }

  auto setBrightness(u8 brightness) -> LEDChain& {
    impl.setBrightness(brightness);
    return *this;
  }

  auto head() -> Color* override {
    return data;
  }

  auto size() -> u16 override {
    return N;
  }

  auto display() -> void {
    for (u16 i = 0; i < N; ++i) {
      Color& c = data[i];
      impl.setPixelColor(i, FloatToByte(c.r), FloatToByte(c.g), FloatToByte(c.b), FloatToByte(c.w));
    }
    impl.show();
  }

private:
  Color data[N];
  Adafruit_NeoPixel impl;
};

}


#endif //RGBLIB_LEDCIRCUIT_H
