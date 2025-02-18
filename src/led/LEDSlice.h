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
  LEDSlice(Color* _head, u16 _size);

  auto head() -> Color* override;
  auto size() -> u16 override;

private:
  Color* _head;
  u16 _size;

};

}

#endif //RGBLIB_LEDSLICE_H
