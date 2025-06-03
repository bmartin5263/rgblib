//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_PIXELSLICE_H
#define RGBLIB_PIXELSLICE_H

#include "PixelList.h"

namespace rgb {

struct Color;
class PixelSlice final : public PixelList {
public:
  PixelSlice(Pixel* head, u16 size);

  auto getHead() -> Pixel* override;
  auto getHead() const -> const Pixel* override;
  auto getSize() const -> u16 override;

private:
  Pixel* mHead;
  u16 mSize;

};

}

#endif //RGBLIB_PIXELSLICE_H
