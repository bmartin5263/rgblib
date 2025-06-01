//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_LEDCHAIN_H
#define RGBLIB_LEDCHAIN_H

#include "Types.h"
#include "Color.h"

namespace rgb {

struct FillChain {
  FillChain(Color* head, u16 size);

  auto fill(const Color& color) -> FillChain;
  auto fill(const Color& color, u16 range) -> FillChain;
  auto fill(const Color& color, u16 start, u16 range) -> FillChain;

  Color* mHead{};
  u16 mSize{};
};

struct Point;
class LEDSlice;
class LEDChain {
public:
  [[nodiscard]] virtual auto getHead() -> Color* = 0;
  [[nodiscard]] virtual auto getHead() const -> const Color* = 0;
  [[nodiscard]] virtual auto getSize() const -> u16 = 0;

  [[nodiscard]] auto get(u16 pixel) -> Color*;
  [[nodiscard]] auto operator[](u16 pixel) -> Color&;
  [[nodiscard]] auto get(Point pixel) -> Color*;
  [[nodiscard]] auto operator[](Point point) -> Color&;

  auto fill(const Color& color) -> FillChain;
  auto fill(const Color& color, u16 range) -> FillChain;
  auto fill(const Color& color, u16 start, u16 range) -> FillChain;
  auto clear() -> void;
  auto set(u16 pixel, const Color& color) -> void;
  auto set(Point pixel, const Color& color) -> void;

  auto slice(u16 length) -> LEDSlice;
  auto slice(u16 start, u16 length) -> LEDSlice;

  [[nodiscard]] auto begin() -> Color*;
  [[nodiscard]] auto begin() const -> const Color*;
  [[nodiscard]] auto end() -> Color*;
  [[nodiscard]] auto end() const -> const Color*;

  LEDChain() = default;
  LEDChain(const LEDChain& rhs) = default;
  LEDChain(LEDChain&& rhs) noexcept = default;
  LEDChain& operator=(const LEDChain& rhs) = default;
  LEDChain& operator=(LEDChain&& rhs) noexcept = default;
  virtual ~LEDChain() = default;
};

using LEDStrip = LEDChain;
using LEDRing = LEDChain;
using LEDGrid = LEDChain;

}

#endif //RGBLIB_LEDCHAIN_H
