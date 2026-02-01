//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_PIXELSLICE_H
#define RGBLIB_PIXELSLICE_H

#include "ContiguousPixelList.h"

namespace rgb {

class PixelSlice : public ContiguousPixelList {
public:
  PixelSlice(Pixel* head, uint size, bool reversed=false);

  auto data() -> Pixel* override;
  auto data() const -> const Pixel* override;
  auto length() const -> uint override;

private:
  Pixel* mHead;
  uint mSize;
};

}

#endif //RGBLIB_PIXELSLICE_H
