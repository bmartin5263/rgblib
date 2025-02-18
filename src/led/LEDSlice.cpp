//
// Created by Brandon on 1/19/25.
//

#include "LEDSlice.h"

namespace rgb {

LEDSlice::LEDSlice(Color* head, u16 size) :
  _head(head), _size(size)
{
}

auto LEDSlice::size() -> u16 {
  return _size;
}

auto LEDSlice::head() -> Color* {
  return _head;
}

}