//
// Created by Brandon on 1/10/26.
//

#include "ContiguousPixelList.h"
#include "Assertions.h"
#include "PixelSlice.h"

namespace rgb {

ContiguousPixelList::ContiguousPixelList(bool reversed): mReversed(reversed) {

}

auto ContiguousPixelList::slice(uint endExclusive) -> PixelSlice {
  return slice(0, endExclusive);
}

auto ContiguousPixelList::slice(uint start, uint endExclusive) -> PixelSlice {
  ASSERT(start < endExclusive, "Slice start must be before end");
  endExclusive = Min(endExclusive, length());
  auto* newData = data() + start;
  auto length = endExclusive - start;
  return PixelSlice{newData, length};
}

auto ContiguousPixelList::set(uint pixel, const Color& color) -> void {
  if (pixel >= length()) {
    return;
  }
  if (mReversed) {
    data()[length() - 1 - pixel] = color;
  }
  else {
    data()[pixel] = color;
  }
}

auto ContiguousPixelList::get(uint pixel) const -> Pixel {
  if (pixel >= length()) {
    return Color::OFF();
  }
  if (mReversed) {
    return data()[length() - 1 - pixel];
  }
  else {
    return data()[pixel];
  }
}

}