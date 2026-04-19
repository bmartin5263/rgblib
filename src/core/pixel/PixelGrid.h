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
  using PixelList::set;

  [[nodiscard]] virtual auto rows() const -> uint = 0;
  [[nodiscard]] virtual auto columns() const -> uint = 0;
  [[nodiscard]] virtual auto get(uint column, uint row) const -> const Pixel* = 0;
  [[nodiscard]] virtual auto get(Point position) const -> const Pixel* = 0;
  virtual auto set(uint column, uint row, const Color& color) -> void = 0;
  virtual auto set(Point position, const Color& color) -> void = 0;
};

}

#endif //RGBLIB_PIXELGRID_H
