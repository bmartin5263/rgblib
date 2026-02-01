//
// Created by Brandon on 1/5/25.
//

#include <utility>
#include "Assertions.h"
#include "PixelList.h"
#include "PixelSlice.h"
#include "rgb/Color.h"
#include "Point.h"

namespace rgb {

#ifdef RGB_DEBUG
constexpr auto DEBUG = true;
#else
constexpr auto DEBUG = false;
#endif

auto PixelList::fill(const Color& color) -> void {
  fill(color, 0, length());
}

auto PixelList::fill(const Color& color, uint range) -> void {
  fill(color, 0, range);
}

auto PixelList::fill(const Color& color, uint start, uint endExclusive) -> void {
  endExclusive = std::min(length(), endExclusive);
  for (auto i = start; i < endExclusive; ++i) {
    set(i, color);
  }
}

auto PixelList::clear() -> void {
  fill(Color::OFF());
}

auto PixelList::begin() -> PixelIterator {
  return {this, 0};
}

auto PixelList::begin() const -> ConstPixelIterator {
  return {const_cast<PixelList*>(this), 0};
}

auto PixelList::end() -> PixelIterator {
  return {this, length()};
}

auto PixelList::end() const -> ConstPixelIterator {
  return {const_cast<PixelList*>(this), length()};
}

}