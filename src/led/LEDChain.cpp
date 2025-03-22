//
// Created by Brandon on 1/5/25.
//

#include "Assertions.h"
#include "LEDChain.h"
#include "LEDSlice.h"
#include "Color.h"
#include "Point.h"

namespace rgb {

auto LEDChain::fill(const Color& color) -> void {
  auto _head = head();
  for (int i = 0; i < size(); ++i) {
    _head[i] = color;
  }
}

//auto LEDChain::clear() -> void {
//  fill(Color::OFF());
//}

auto LEDChain::get(u16 pixel) -> Color* {
  ASSERT(pixel >= 0 && pixel < size(), "Pixel is out of bounds");
  return head() + pixel;
}

auto LEDChain::get(Point point) -> Color* {
  u16 pixel = (size() * point.x) + point.y;
  ASSERT(pixel >= 0 && pixel < size(), "Pixel is out of bounds");
  return head() + pixel;
}

auto LEDChain::set(u16 pixel, const Color& color) -> void {
  ASSERT(pixel >= 0, "Pixel is negative");
  ASSERT(pixel < size(), "Pixel is out of bounds");
  *get(pixel) = color;
}

auto LEDChain::set(Point point, const Color& color) -> void {
  this->operator[](point) = color;
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
  auto N = size();
  auto data = head();

  ASSERT(start < N, "Slice start is beyond length of chain");
  u16 end = start + length;
  ASSERT(end < N, "Slice end is beyond length of chain");

  Color* head = data + start;
  return {head, length};
}

}