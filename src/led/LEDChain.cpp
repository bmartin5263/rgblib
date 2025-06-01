//
// Created by Brandon on 1/5/25.
//

#include "Assertions.h"
#include "LEDChain.h"
#include "LEDSlice.h"
#include "Color.h"
#include "Point.h"

namespace rgb {

auto LEDChain::fill(const Color& color) -> FillChain {
  return fill(color, 0, getSize());
}

auto LEDChain::fill(const Color& color, u16 range) -> FillChain {
  return fill(color, 0, range);
}

auto LEDChain::fill(const Color& color, u16 start, u16 range) -> FillChain {
  for (int i = 0; i < range; ++i) {
    *get(start + i) = color;
  }
  auto end = start + range;
  auto newSize = static_cast<u16>(getSize() - end);
  return { getHead() + end, newSize };
}

auto LEDChain::clear() -> void {
  fill(Color::OFF());
}

auto LEDChain::get(u16 pixel) -> Color* {
  ASSERT(pixel >= 0, "Pixel is negative");
  ASSERT(pixel < getSize(), "Pixel is out of bounds");
  return getHead() + pixel;
}

auto LEDChain::get(Point point) -> Color* {
  u16 pixel = (getSize() * point.x) + point.y;
  ASSERT(pixel >= 0, "Pixel is negative");
  ASSERT(pixel < getSize(), "Pixel is out of bounds");
  return getHead() + pixel;
}

auto LEDChain::set(u16 pixel, const Color& color) -> void {
  *get(pixel) = color;
}

auto LEDChain::set(Point point, const Color& color) -> void {
  *get(point) = color;
}

auto LEDChain::operator[](u16 pixel) -> Color& {
  return *get(pixel);
}

auto LEDChain::operator[](Point point) -> Color& {
  return *get(point);
}

auto LEDChain::slice(u16 length) -> LEDSlice {
  return slice(0, length);
}

auto LEDChain::slice(u16 start, u16 length) -> LEDSlice {
  auto N = getSize();
  auto data = getHead();

  ASSERT(start < N, "Slice start is beyond length of chain");
  auto end = start + length;
  ASSERT(end <= N, "Slice end is beyond length of chain");

  Color* head = data + start;
  return {head, length};
}

auto LEDChain::begin() -> Color* {
  return getHead();
}

auto LEDChain::begin() const -> const Color* {
  return getHead();
}

auto LEDChain::end() -> Color* {
  return getHead() + getSize();
}

auto LEDChain::end() const -> const Color* {
  return getHead() + getSize();
}

FillChain::FillChain(rgb::Color* head, rgb::u16 size): mHead(head), mSize(size) {

}

auto FillChain::fill(const rgb::Color& color) -> FillChain {
  return fill(color, 0, mSize);
}

auto FillChain::fill(const rgb::Color& color, u16 range) -> FillChain {
  return fill(color, 0, range);
}

auto FillChain::fill(const Color& color, u16 start, u16 range) -> FillChain {
  for (int i = 0; i < range; ++i) {
    mHead[start + i] = color;
  }
  auto end = start + range;
  auto newSize = static_cast<u16>(mSize - end);
  return { mHead + end, newSize };
}

}