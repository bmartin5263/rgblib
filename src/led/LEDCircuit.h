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
#include "Drawable.h"

namespace rgb {

template <u16 N>
class LEDCircuit : public LEDChain, public Drawable {
public:
  explicit LEDCircuit(pin_num pin, u16 offset = 0, neoPixelType type = NEO_GRBW + NEO_KHZ800):
    data{}, impl(N, pin, type), mOffset(offset), mReversed(false)
  {
    start();
  }

  auto start() -> void {
    impl.begin();
  }

  auto setBrightness(u8 brightness) -> LEDCircuit& {
    impl.setBrightness(brightness);
    return *this;
  }

  auto getHead() -> Color* override {
    return data;
  }

  auto getHead() const -> const Color* override {
    return data;
  }

  auto getSize() const -> u16 override {
    return N;
  }

  auto getOffset() const -> u16 {
    return mOffset;
  }

  auto reset() -> void override {
    clear();
  }

  auto display() -> void override {
    if (mReversed) {
      for (u16 i = 0; i < N; ++i) {
        auto& c = data[mapPixelToLED(N - 1 - i)];
        impl.setPixelColor(i, FloatToByte(c.r), FloatToByte(c.g), FloatToByte(c.b), FloatToByte(c.w));
      }
    }
    else {
      for (u16 i = 0; i < N; ++i) {
        auto& c = data[mapPixelToLED(i)];
        impl.setPixelColor(i, FloatToByte(c.r), FloatToByte(c.g), FloatToByte(c.b), FloatToByte(c.w));
      }
    }
    impl.show();
  }

  auto setOffset(int amount) -> void {
    mOffset = amount;
  }

  auto setReversed(bool value) -> void {
    mReversed = value;
  }

  auto isReversed() const -> bool {
    return mReversed;
  }

  auto toggleReversed() -> bool {
    auto reversed = isReversed();
    setReversed(!reversed);
    return reversed;
  }

  auto mapPixelToLED(u16 pixel) -> u16 {
    return (pixel + mOffset) % N;
  }

private:
  Color data[N];
  Adafruit_NeoPixel impl;
  int mOffset;
  bool mReversed;
};

}


#endif //RGBLIB_LEDCIRCUIT_H
