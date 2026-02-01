//
// Created by Brandon on 1/10/26.
//

#ifndef RGBLIB_REVERSEPIXELLIST_H
#define RGBLIB_REVERSEPIXELLIST_H

#include "PixelList.h"

namespace rgb {

class ReversePixelList : public PixelList {
public:
  explicit ReversePixelList(PixelList& source);

  auto length() const -> uint override;
  auto get(uint pixel) const -> Pixel override;
  auto set(uint pixel, const Color& color) -> void override;

private:
  PixelList& mSource;
};

}

#endif //RGBLIB_REVERSEPIXELLIST_H
