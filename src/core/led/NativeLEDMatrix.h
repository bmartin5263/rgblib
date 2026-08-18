//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_NATIVELEDMATRIX_H
#define RGBLIB_NATIVELEDMATRIX_H

#include "Types.h"
#include "Util.h"
#include "ContiguousPixelGrid.h"
#include "LEDDevice.h"
#include "NativeDisplay.h"
#include "NativeRenderable.h"

namespace rgb {

/**
 * Backs a PixelGrid with an SDL-rendered window instead of physical LEDs,
 * for running an application with no hardware present.
 */
template <uint COLUMNS, uint ROWS>
class NativeLEDMatrix : public ContiguousPixelGrid, public LEDDevice, public NativeRenderable {
public:
  static constexpr auto N = COLUMNS * ROWS;

  constexpr explicit NativeLEDMatrix(
    int offset = 0
  ):
    pixels{}, offset{offset}, brightness(1.0f), reversed{false}, started{false}
  {
  }

  auto start() -> void override {
    if (started) {
      return;
    }

    NativeDisplay::RegisterMatrix(*this);
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

  // Satisfies both PixelGrid::columns() and NativeRenderable::columns().
  auto columns() const -> uint override {
    return COLUMNS;
  }

  auto pixelScale() const -> normal override {
    return 1.0f;
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

  auto mapPixelToLED(u16 pixel) const -> u16 {
    return WrapIndex(pixel, offset, static_cast<u16>(N));
  }

  auto pixelCount() const -> u16 override {
    return static_cast<u16>(N);
  }

  auto renderedPixel(u16 index) const -> Pixel override {
    auto mapped = reversed ? mapPixelToLED(static_cast<u16>(N - 1 - index)) : mapPixelToLED(index);
    return pixels[mapped] * brightness;
  }

  NativeLEDMatrix(const NativeLEDMatrix&) = delete;
  NativeLEDMatrix& operator=(const NativeLEDMatrix&) = delete;
  NativeLEDMatrix(NativeLEDMatrix&&) = default;
  NativeLEDMatrix& operator=(NativeLEDMatrix&&) = default;

private:
  Pixel pixels[N];
  int offset;
  normal brightness;
  bool reversed;
  bool started;
};

}

#endif //RGBLIB_NATIVELEDMATRIX_H
