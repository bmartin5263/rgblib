//
// Created by Brandon on 10/26/26.
//

#ifndef RGBLIB_PIXELBUFFER_H
#define RGBLIB_PIXELBUFFER_H

#include <array>
#include "ContiguousPixelList.h"

namespace rgb {

template<uint N>
class PixelBuffer : public ContiguousPixelList {
public:
  [[nodiscard]] auto length() const -> uint override { return N; }
  auto data() -> Pixel* override { return mData.data(); }
  auto data() const -> const Pixel* override { return mData.data(); }

private:
  std::array<Pixel, N> mData;
};

}

#endif //RGBLIB_PIXELBUFFER_H
