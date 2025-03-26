//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_LEDSLICE_H
#define RGBLIB_LEDSLICE_H

#include "LEDChain.h"

namespace rgb {

struct Color;
class LEDSlice final : public LEDChain {
public:
  LEDSlice(Color* head, u16 size, u16 rotation = 0);

  auto head() -> Color* override;
  auto size() -> u16 override;
  auto getShift() -> u16 override;
  auto setShift(u16 amount) -> void override;

private:
  Color* mHead;
  u16 mSize;
  u16 mRotation;

};

}

#endif //RGBLIB_LEDSLICE_H
