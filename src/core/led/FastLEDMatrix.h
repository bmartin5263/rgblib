//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_FASTLEDMATRIX_H
#define RGBLIB_FASTLEDMATRIX_H

#include <FastLED.h>
#include "Types.h"
#include "Pin.h"
#include "Assertions.h"
#include "RgbColor.h"
#include "ContiguousPixelList.h"
#include "LEDCircuit.h"
#include "Log.h"
#include "ContiguousPixelGrid.h"
#include "RgbwSupport.h"

namespace rgb {

template <uint COLUMNS, uint ROWS, uint PIN, RgbwSupport WHITE_SUPPORT=RgbwSupport::DISABLE, bool STAGGER = false>
class FastLEDMatrix : public ContiguousPixelGrid, public LEDCircuit {
public:
  static constexpr auto N = COLUMNS * ROWS;

  constexpr explicit FastLEDMatrix(u16 offset = 0):
    leds{}, pixels{}, offset{offset}, reversed{false}, started{false}
  {
  }

  auto start() -> void override {
    if (started) {
      return;
    }

    if constexpr (WHITE_SUPPORT == RgbwSupport::ENABLE) {
      FastLED.addLeds<WS2812B, PIN, GRB>(leds, N).setRgbw();
    }
    else {
      FastLED.addLeds<WS2812B, PIN, GRB>(leds, N);
    }
    INFO("Started %i LEDs on Pin %i", N, PIN);

    started = true;
  }

  auto data() -> Pixel* override {
    return pixels;
  }

  auto data() const -> const Pixel* override {
    return pixels;
  }

  auto length() const -> uint override {
    return N;
  }

  auto rows() const -> uint override {
    return ROWS;
  }

  auto columns() const -> uint override {
    return COLUMNS;
  }

  auto getOffset() const -> int {
    return offset;
  }

  auto setOffset(int amount) -> void {
    offset = amount;
  }

  auto getBrightness() const -> normal {
    return brightness;
  }

  auto setBrightness(normal amount) -> void {
    brightness = Clamp(amount, 0.0f, 1.0f);
  }

  auto reset() -> void override {
    clear();
  }

  auto display() -> void override {
    if (reversed) {
      for (u16 i = 0; i < N; ++i) {
        auto pixel = pixels[pixelPositionToLEDPosition(N - 1 - i)] * brightness;
        leds[i] = CRGB(FloatToByte(pixel.r), FloatToByte(pixel.g), FloatToByte(pixel.b));
      }
    }
    else {
      for (u16 i = 0; i < N; ++i) {
        auto pixel = pixels[i];
        auto ledPosition = pixelPositionToLEDPosition(i);
        if constexpr (STAGGER) {
          ledPosition = zigzagToLinearIndex(ledPosition);
        }
        leds[ledPosition] = CRGB(FloatToByte(pixel.r), FloatToByte(pixel.g), FloatToByte(pixel.b));
      }
    }
  }

  auto setReversed(bool value) -> void {
    reversed = value;
  }

  auto isReversed() const -> bool {
    return reversed;
  }

  auto toggleReversed() -> bool {
    auto previous = reversed;
    setReversed(!reversed);
    return previous;
  }

  int zigzagToLinearIndex(int index) {
    int row = index / COLUMNS;
    int columnInRow = index % COLUMNS;

    if (row % 2 == 0) {
      return row * COLUMNS + (COLUMNS - 1 - columnInRow);
    } else {
      return row * COLUMNS + columnInRow;
    }
  }

  auto pixelPositionToLEDPosition(u16 pixel) -> u16 {
    return (pixel + offset) % N;
  }

private:
  CRGB leds[N];
  Pixel pixels[N];
  int offset;
  normal brightness;
  bool reversed;
  bool started;
};

}


#endif //RGBLIB_FASTLEDMATRIX_H
