//
// Created by Brandon on 1/19/25.
//

#include "LEDSlice.h"

namespace rgb {

LEDSlice::LEDSlice(Color* head, u16 size, u16 rotation) :
  mHead(head), mSize(size), mOffset(rotation)
{
}

auto LEDSlice::getSize() const -> u16 {
  return mSize;
}

auto LEDSlice::getHead() -> Color* {
  return mHead;
}

auto LEDSlice::getHead() const -> const Color* {
  return mHead;
}

auto LEDSlice::getOffset() const -> u16 {
  return mOffset;
}

auto LEDSlice::setOffset(int amount) -> void {
  mOffset = amount;
}

auto LEDSlice::isReversed() const -> bool {
  return mReversed;
}

auto LEDSlice::setReversed(bool value) -> void {
  mReversed = value;
}

}