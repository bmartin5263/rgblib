//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_LEDMATRIX_H
#define RGBLIB_LEDMATRIX_H

#include <Adafruit_NeoPixel.h>
#include "Types.h"
#include "Assertions.h"
#include "Color.h"
#include "PixelList.h"
#include "PixelSlice.h"
#include "LEDList.h"

namespace rgb {

template <u16 COLUMNS, u16 ROWS, bool STAGGER = false>
class LEDMatrix : public PixelList, public LEDList {
public:
  static constexpr auto N = COLUMNS * ROWS;

  explicit LEDMatrix(pin_num pin, neoPixelType type = NEO_GRBW + NEO_KHZ800, u16 offset = 0):
    pixels{}, leds(N, pin, type), mOffset(offset), mReversed(false)
  {
    start();
  }

  auto start() -> void {
    leds.begin();
  }

  auto setBrightness(u8 brightness) -> LEDMatrix& {
    leds.setBrightness(brightness);
    return *this;
  }

  auto getHead() -> Pixel* override {
    return pixels;
  }

  auto getHead() const -> const Pixel* override {
    return pixels;
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

  int zigzagToLinearIndex(int index) {
    int col = index / ROWS;
    int rowInCol = index % ROWS;

    if (col % 2 == 0) {
      // Even column: top-down
      return col * ROWS + rowInCol;
    } else {
      // Odd column: bottom-up
      return col * ROWS + (ROWS - 1 - rowInCol);
    }
  }

  auto display() -> void override {
    if (mReversed) {
      for (u16 i = 0; i < N; ++i) {
        auto& c = pixels[mapPixelToLED(N - 1 - i)];
        leds.setPixelColor(i, FloatToByte(c.r), FloatToByte(c.g), FloatToByte(c.b), FloatToByte(c.w));
      }
    }
    else {
      if constexpr (STAGGER) {
        for (u16 i = 0; i < N; ++i) {
          auto pixel = pixels[i];
          auto led = mapPixelToLED(i);
          leds.setPixelColor(zigzagToLinearIndex(led), FloatToByte(pixel.r), FloatToByte(pixel.g), FloatToByte(pixel.b), FloatToByte(pixel.w));
        }
      }
      else {
        for (u16 i = 0; i < N; ++i) {
          auto pixel = pixels[i];
          auto led = mapPixelToLED(i);
          leds.setPixelColor(led, FloatToByte(pixel.r), FloatToByte(pixel.g), FloatToByte(pixel.b), FloatToByte(pixel.w));
        }
      }
    }
    leds.show();
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
  Pixel pixels[N];
  Adafruit_NeoPixel leds;
  int mOffset;
  int stagger;
  bool mReversed;
};

}


#endif //RGBLIB_LEDMATRIX_H
