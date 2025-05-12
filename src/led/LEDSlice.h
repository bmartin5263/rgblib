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
  LEDSlice(Color* head, u16 size);

  auto getHead() -> Color* override;
  auto getHead() const -> const Color* override;
  auto getSize() const -> u16 override;

private:
  Color* mHead;
  u16 mSize;

};

}

#endif //RGBLIB_LEDSLICE_H
