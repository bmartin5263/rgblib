//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_PIXELGRID_H
#define RGBLIB_PIXELGRID_H

#include "PixelList.h"

namespace rgb {

struct Point;
class PixelSlice;
class PixelGrid : public PixelList {
public:
  virtual auto getColumns() -> size_t;

  [[nodiscard]] auto get(Point point) -> Pixel*;
  [[nodiscard]] auto operator[](Point point) -> Pixel&;
  auto set(Point point, const Color& color) -> void;
};

}

#endif //RGBLIB_PIXELGRID_H
