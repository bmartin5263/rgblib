//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_LEDCHAIN_H
#define RGBLIB_LEDCHAIN_H

#include "Types.h"
#include "Color.h"

namespace rgb {

struct Point;
class LEDSlice;
class LEDChain {
public:
  virtual auto head() -> Color* = 0;
  virtual auto size() -> u16 = 0;
  virtual auto setShift(u16 amount) -> void = 0;
  virtual auto getShift() -> u16 = 0;

  auto get(u16 pixel) -> Color*;
  auto operator[](u16 pixel) -> Color&;
  auto get(Point pixel) -> Color*;
  auto operator[](Point point) -> Color&;

  auto fill(const Color& color) -> void;
  auto clear() -> void;
  auto set(u16 pixel, const Color& color) -> void;
  auto set(Point pixel, const Color& color) -> void;

  auto slice(u16 length) -> LEDSlice;
  auto slice(u16 start, u16 length) -> LEDSlice;

  virtual ~LEDChain() = default;

private:
  static auto mapPixelToLED(u16 pixel, u16 rotation, u16 size) -> u16;

};

using LEDStrip = LEDChain;
using LEDRing = LEDChain;
using LEDGrid = LEDChain;

}

#endif //RGBLIB_LEDCHAIN_H
