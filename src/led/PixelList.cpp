//
// Created by Brandon on 1/5/25.
//

#include "Assertions.h"
#include "PixelList.h"
#include "PixelSlice.h"
#include "Color.h"
#include "Point.h"

namespace rgb {

auto PixelList::fill(const Color& color) -> FillChain {
  return fill(color, 0, getSize());
}

auto PixelList::fill(const Color& color, u16 range) -> FillChain {
  return fill(color, 0, range);
}

auto PixelList::fill(const Color& color, u16 start, u16 range) -> FillChain {
  for (int i = 0; i < range; ++i) {
    *get(start + i) = color;
  }
  auto end = start + range;
  auto newSize = static_cast<u16>(getSize() - end);
  return { getHead() + end, newSize };
}

auto PixelList::clear() -> void {
  fill(Color::OFF());
}

auto PixelList::get(u16 pixel) -> Pixel* {
  ASSERT(pixel >= 0, "Pixel is negative");
  ASSERT(pixel < getSize(), "Pixel is out of bounds");
  return getHead() + pixel;
}

auto PixelList::set(u16 pixel, const Color& color) -> void {
  *get(pixel) = color;
}


auto PixelList::operator[](u16 pixel) -> Color& {
  return *get(pixel);
}

auto PixelList::slice(u16 length) -> PixelSlice {
  return slice(0, length);
}

auto PixelList::slice(u16 start, u16 length) -> PixelSlice {
  auto N = getSize();
  auto data = getHead();

  ASSERT(start < N, "Slice start is beyond length of chain");
  auto end = start + length;
  ASSERT(end <= N, "Slice end is beyond length of chain");

  auto* head = data + start;
  return {head, length};
}

auto PixelList::begin() -> Pixel* {
  return getHead();
}

auto PixelList::begin() const -> const Pixel* {
  return getHead();
}

auto PixelList::end() -> Pixel* {
  return getHead() + getSize();
}

auto PixelList::end() const -> const Pixel* {
  return getHead() + getSize();
}

FillChain::FillChain(rgb::Pixel* head, rgb::u16 size): mHead(head), mSize(size) {

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