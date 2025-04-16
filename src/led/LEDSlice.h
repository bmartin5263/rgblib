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

  auto getHead() -> Color* override;
  auto getHead() const -> const Color* override;
  auto getSize() const -> u16 override;
  auto getOffset() const -> u16 override;
  auto setOffset(int amount) -> void override;
  auto isReversed() const -> bool override;
  auto setReversed(bool value) -> void override;

private:
  Color* mHead;
  u16 mSize;
  int mOffset;
  bool mReversed;

};

}

#endif //RGBLIB_LEDSLICE_H
