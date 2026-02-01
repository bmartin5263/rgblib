//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_PIXELGRID_H
#define RGBLIB_PIXELGRID_H

#include "PixelList.h"
#include "Point.h"

namespace rgb {

class PixelGrid : public PixelList {
public:
  using PixelList::get;
  [[nodiscard]] virtual auto get(uint column, uint row) const -> const Pixel* = 0;

  [[nodiscard]] auto get(Point point) -> Pixel*;
  [[nodiscard]] auto get(Point point) const -> const Pixel*;
  [[nodiscard]] auto get(uint column, uint row) -> Pixel*;
  [[nodiscard]] auto operator[](Point point) -> Pixel&;
  [[nodiscard]] auto operator[](Point point) const -> const Pixel&;
};

}

#endif //RGBLIB_PIXELGRID_H
