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
  auto N = length();
  ASSERT(endExclusive < N, "Slice end is beyond length of chain");
  ASSERT(start < endExclusive, "Start must be before end");

  auto* newData = data() + start;
  auto length = endExclusive - start;
  return PixelSlice{newData, length};
}

auto ContiguousPixelList::set(uint pixel, const Color& color) -> void {
  if (mReversed) {
    data()[length() - 1 - pixel] = color;
  }
  else {
    data()[pixel] = color;
  }
}

auto ContiguousPixelList::get(uint pixel) const -> Pixel {
  ASSERT(pixel >= 0, "Pixel is negative");
  ASSERT(pixel < length(), "Pixel is out of bounds");
  if (mReversed) {
    return data()[length() - 1 - pixel];
  }
  else {
    return data()[pixel];
  }
}

}