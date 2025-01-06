//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_LEDCHAIN_H
#define RGBLIB_LEDCHAIN_H

#include "core/Types.h"

struct Color;
struct Point;
class LEDChain {
public:
  virtual auto operator[](u16 pixel) -> Color&;
  virtual auto operator[](Point point) -> Color&;
  virtual auto size() -> u16 = 0;
  virtual auto head() -> Color* = 0;

  virtual auto fill(const Color& color) -> void;
  virtual auto set(u16 pixel, const Color& color) -> void;
  virtual auto get(u16 pixel) -> Color*;
  virtual auto set(Point pixel, const Color& color) -> void;
  virtual auto get(Point pixel) -> Color*;

  virtual ~LEDChain() = default;

private:

};

#endif //RGBLIB_LEDCHAIN_H
