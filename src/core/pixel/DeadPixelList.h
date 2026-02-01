//
// Created by Brandon on 1/17/26.
//

#ifndef RGBLIB_DEADPIXELLIST_H
#define RGBLIB_DEADPIXELLIST_H

#include "PixelList.h"

namespace rgb {

class DeadPixelList : public PixelList {
public:
  explicit DeadPixelList(uint length);
  auto get(uint pixel) const -> Pixel override;
  auto set(uint pixel, const Color& color) -> void override;
  auto length() const -> uint override;

private:
  uint mLength{};
};


}

#endif //RGBLIB_DEADPIXELLIST_H
