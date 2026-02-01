//
// Created by Brandon on 1/19/25.
//

#include "PixelSlice.h"
#include "Assertions.h"

namespace rgb {

PixelSlice::PixelSlice(Pixel* head, uint size, bool reversed) :
  ContiguousPixelList(reversed), mHead(head), mSize(size)
{
}

auto PixelSlice::length() const -> uint {
  return mSize;
}

auto PixelSlice::data() -> Pixel* {
  return mHead;
}

auto PixelSlice::data() const -> const Pixel* {
  return mHead;
}

}