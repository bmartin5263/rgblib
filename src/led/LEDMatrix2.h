//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_LEDMATRIX_H
#define RGBLIB_LEDMATRIX_H

#include <Adafruit_NeoPixel.h>
#include "Types.h"
#include "Assertions.h"
#include "PixelGrid.h"
#include "LEDCircuit.h"
#include "Point.h"
#include "MatrixStrategy.h"

namespace rgb {

template <u16 COLUMNS, u16 ROWS, MatrixStrategy STRATEGY = PixelRowMatrixColumn{}, u16 MATRIX_COLUMNS = 1, u16 MATRIX_ROWS = 1>
class LEDMatrix2 : public PixelGrid, public LEDCircuit {
public:
  static constexpr auto EFFECTIVE_ROWS = ROWS * MATRIX_ROWS;
  static constexpr auto EFFECTIVE_COLS = COLUMNS * MATRIX_COLUMNS;
  static constexpr auto SIZE = EFFECTIVE_ROWS * EFFECTIVE_COLS;

  explicit LEDMatrix2(pin_num pin, neoPixelType type = NEO_GRBW + NEO_KHZ800):
    pixels{}, leds(SIZE, pin, type)
  {
    start();
  }

  auto start() -> void {
    leds.begin();
  }

  auto setBrightness(u8 brightness) -> LEDMatrix2& {
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
    return SIZE;
  }

  auto reset() -> void override {
    clear();
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

  auto display() -> void override {
    auto context = MatrixContext {
      COLUMNS,
      ROWS,
      COLUMNS * ROWS,
      MATRIX_COLUMNS,
      MATRIX_ROWS,
      0,
      0,
      0
    };
    for (u16 pixelNum = 0; pixelNum < SIZE; ++pixelNum) {
      context.pixelNum = pixelNum;
      auto c = pixels[pixelNum];
      auto ledNum = STRATEGY(context);
      leds.setPixelColor(ledNum, FloatToByte(c.r), FloatToByte(c.g), FloatToByte(c.b), FloatToByte(c.w));
    }

    for (u16 row = 0; row < EFFECTIVE_ROWS; ++row) {
      context.pixelRow = row;
      auto& rowData = pixels[row];
      for (u16 col = 0; col < EFFECTIVE_COLS; ++col) {
        context.pixelCol = col;
        auto c = rowData[col];
        auto ledNum = STRATEGY(context);
        leds.setPixelColor(ledNum, FloatToByte(c.r), FloatToByte(c.g), FloatToByte(c.b), FloatToByte(c.w));
      }
    }

    leds.show();
  }

  auto get(Point point) -> Pixel* override {
    ASSERT(point.x >= 0, "Point.X is negative");
    ASSERT(point.y >= 0, "Pixel.Y is negative");
    ASSERT(point.x < COLUMNS, "Pixel.X is out of bounds");
    ASSERT(point.y < ROWS, "Pixel.Y is out of bounds");
    return pixels[point.y][point.x];
  }

  auto set(Point point, const Color& color) -> void override {
    pixels[point.y][point.x] = color;
  }

  auto operator[](Point point) -> Color& override {
    return *(pixels[point.y][point.x]);
  }

private:
  Pixel pixels[EFFECTIVE_ROWS][EFFECTIVE_COLS];
  Adafruit_NeoPixel leds;
};

}


#endif //RGBLIB_LEDMATRIX_H
