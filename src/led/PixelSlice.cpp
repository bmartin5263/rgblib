//
// Created by Brandon on 1/19/25.
//

#include "PixelSlice.h"

namespace rgb {

PixelSlice::PixelSlice(Pixel* head, u16 size) :
  mHead(head), mSize(size)
{
}

auto PixelSlice::getSize() const -> u16 {
  return mSize;
}

auto PixelSlice::getHead() -> Pixel* {
  return mHead;
}

auto PixelSlice::getHead() const -> const Pixel* {
  return mHead;
}

}