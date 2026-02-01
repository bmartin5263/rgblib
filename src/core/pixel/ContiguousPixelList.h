//
// Created by Brandon on 1/10/26.
//

#ifndef RGBLIB_CONTIGUOUSPIXELLIST_H
#define RGBLIB_CONTIGUOUSPIXELLIST_H

#include "PixelList.h"

namespace rgb {
class PixelSlice;
class ContiguousPixelList : public PixelList {
public:
  explicit ContiguousPixelList(bool reversed = false);

  virtual auto data() -> Pixel* = 0;
  virtual auto data() const -> const Pixel* = 0;

  auto slice(uint length) -> PixelSlice;
  auto slice(uint start, uint length) -> PixelSlice;
  auto get(uint pixel) const -> Pixel override;
  auto set(uint pixel, const Color& color) -> void override;

protected:
  bool mReversed;
};


}

#endif //RGBLIB_CONTIGUOUSPIXELLIST_H
