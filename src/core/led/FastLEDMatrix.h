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
#include "MatrixStrategy.h"

namespace rgb {

template <
  uint COLUMNS,
  uint ROWS,
  uint PIN,
  RgbwSupport RGBW_SUPPORT = RgbwSupport::DISABLE,
  uint MULTI_MATRIX_ROWS = 1,
  uint MULTI_MATRIX_COLS = 1,
  typename MULTI_MATRIX_STRATEGY = PixelRowMatrixColumn
>
class FastLEDMatrix : public ContiguousPixelGrid, public LEDCircuit {
public:
  static_assert(MULTI_MATRIX_ROWS > 0, "MULTI_MATRIX_ROWS must be greater than 0");
  static_assert(MULTI_MATRIX_COLS > 0, "MULTI_MATRIX_COLS must be greater than 0");

  static constexpr auto EFFECTIVE_COLUMNS = COLUMNS * MULTI_MATRIX_COLS;
  static constexpr auto EFFECTIVE_ROWS = ROWS * MULTI_MATRIX_ROWS;
  static constexpr auto N = EFFECTIVE_COLUMNS * EFFECTIVE_ROWS;

  constexpr explicit FastLEDMatrix(int offset = 0):
    leds{}, pixels{}, offset{offset}, brightness{1.0f}, reversed{false}, started{false}
  {
  }

  auto start() -> void override {
    if (started) {
      return;
    }

    if constexpr (RGBW_SUPPORT == RgbwSupport::ENABLE) {
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
    return EFFECTIVE_ROWS;
  }

  auto columns() const -> uint override {
    return EFFECTIVE_COLUMNS;
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
      for (uint i = 0; i < N; ++i) {
        auto pixel = pixels[pixelPositionToLEDPosition(N - 1 - i)] * brightness;
        leds[i] = CRGB(FloatToByte(pixel.r), FloatToByte(pixel.g), FloatToByte(pixel.b));
      }
    }
    else {
      for (uint i = 0; i < N; ++i) {
        auto pixel = pixels[i] * brightness;
        auto ledPosition = pixelPositionToLEDPosition(i);
        if (ledPosition >= N) {
          break;
        }
//        if constexpr (STAGGER) {
//          ledPosition = zigzagToLinearIndex(ledPosition);
//        }
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

  auto pixelPositionToLEDPosition(uint pixel) -> uint {
    const auto rotated = (pixel + offset) % N;
    const auto logicalRow = rotated / EFFECTIVE_COLUMNS;
    const auto logicalColumn = rotated % EFFECTIVE_COLUMNS;
    return MULTI_MATRIX_STRATEGY::indexOf(
      logicalColumn, logicalRow, COLUMNS, ROWS, MULTI_MATRIX_COLS, MULTI_MATRIX_ROWS
    );
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
