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

template <u16 N>
class LEDCircuit : public LEDChain {
public:
  LEDCircuit(Adafruit_NeoPixel& impl): impl(&impl) {

  }

  auto head() -> Color* override {
    return data;
  }

  auto size() -> u16 override {
    return N;
  }

  auto display() -> void {
    impl->clear();
    auto c = head();
    for (u16 i = 0; i < N; ++i) {
      impl->setPixelColor(FloatToByte(c->r), FloatToByte(c->g), FloatToByte(c->b), FloatToByte(c->w));
      ++c;
    }
    impl->show();
  }

private:
  Adafruit_NeoPixel* impl;
  Color data[N];

  static auto FloatToByte(float f, u8 range = 255) -> u8 {
    return ((u8)(f * range)) % (range + 1);
  }
};


#endif //RGBLIB_LEDCIRCUIT_H
