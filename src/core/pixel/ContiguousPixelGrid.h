//
// Created by Brandon on 4/19/26.
//

#ifndef RGBLIB_CONTIGUOUSPIXELGRID_H
#define RGBLIB_CONTIGUOUSPIXELGRID_H

#include "PixelGrid.h"

namespace rgb {

class ContiguousPixelGrid : public PixelGrid {
public:
  virtual auto data() -> Pixel* = 0;
  virtual auto data() const -> const Pixel* = 0;

  auto get(uint pixel) const -> Pixel override;
  auto get(uint column, uint row) const -> Pixel override;
  auto get(Point position) const -> Pixel override;

  auto set(uint pixel, const Color& color) -> void override;
  auto set(uint column, uint row, const Color& color) -> void override;
  auto set(Point position, const Color& color) -> void override;
};

}

#endif //RGBLIB_CONTIGUOUSPIXELGRID_H
