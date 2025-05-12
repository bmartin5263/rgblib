//
// Created by Brandon on 1/19/25.
//

#include "LEDSlice.h"

namespace rgb {

LEDSlice::LEDSlice(Color* head, u16 size) :
  mHead(head), mSize(size)
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

}