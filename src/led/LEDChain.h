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
  // Accessors
  virtual auto head() -> Color* = 0;
  virtual auto size() -> u16 = 0;
  virtual auto get(u16 pixel) -> Color*;
  virtual auto operator[](u16 pixel) -> Color&;
  virtual auto get(Point pixel) -> Color*;
  virtual auto operator[](Point point) -> Color&;

  // Mutators
  virtual auto fill(const Color& color) -> void;
  virtual auto set(u16 pixel, const Color& color) -> void;
  virtual auto set(Point pixel, const Color& color) -> void;

  virtual auto slice(u16 length) -> LEDSlice;
  virtual auto slice(u16 start, u16 length) -> LEDSlice;

  virtual ~LEDChain() = default;

private:

};

using LEDStrip = LEDChain;
using LEDRing = LEDChain;
using LEDGrid = LEDChain;

}

#endif //RGBLIB_LEDCHAIN_H
