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
  [[nodiscard]] virtual auto getHead() -> Color* = 0;
  [[nodiscard]] virtual auto getHead() const -> const Color* = 0;
  [[nodiscard]] virtual auto getSize() const -> u16 = 0;

  virtual auto setOffset(int amount) -> void = 0;
  [[nodiscard]] virtual auto getOffset() const -> u16 = 0;
  virtual auto setReversed(bool value) -> void = 0;
  [[nodiscard]] virtual auto isReversed() const -> bool = 0;
  auto toggleReversed() -> bool;

  [[nodiscard]] auto get(u16 pixel) -> Color*;
  [[nodiscard]] auto operator[](u16 pixel) -> Color&;
  [[nodiscard]] auto get(Point pixel) -> Color*;
  [[nodiscard]] auto operator[](Point point) -> Color&;

  auto fill(const Color& color) -> void;
  auto clear() -> void;
  auto set(u16 pixel, const Color& color) -> void;
  auto set(Point pixel, const Color& color) -> void;

  auto slice(u16 length) -> LEDSlice;
  auto slice(u16 start, u16 length) -> LEDSlice;

  [[nodiscard]] auto begin() -> Color*;
  [[nodiscard]] auto begin() const -> const Color*;
  [[nodiscard]] auto end() -> Color*;
  [[nodiscard]] auto end() const -> const Color*;

  virtual ~LEDChain() = default;


private:
  static auto mapPixelToLED(u16 pixel, u16 rotation, u16 size) -> u16;

};

using LEDStrip = LEDChain;
using LEDRing = LEDChain;
using LEDGrid = LEDChain;

}

#endif //RGBLIB_LEDCHAIN_H
