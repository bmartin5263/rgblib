//
// Created by Brandon on 1/19/25.
//

#include "LEDSlice.h"

namespace rgb {

LEDSlice::LEDSlice(Color* head, u16 size, u16 rotation) :
  mHead(head), mSize(size), mRotation(rotation)
{
}

auto LEDSlice::size() -> u16 {
  return mSize;
}

auto LEDSlice::head() -> Color* {
  return mHead;
}

auto LEDSlice::getShift() -> u16 {
  return mRotation;
}

auto LEDSlice::setShift(u16 amount) -> void {
  mRotation = amount;
}

}