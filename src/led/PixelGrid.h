//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_PIXELGRID_H
#define RGBLIB_PIXELGRID_H

#include "PixelList.h"

namespace rgb {

struct Point;
class PixelGrid : public PixelList {
public:
  [[nodiscard]] virtual auto get(Point point) -> Pixel*;
  [[nodiscard]] virtual auto operator[](Point point) -> Pixel&;
  virtual auto set(Point point, const Color& color) -> void;
};

}

#endif //RGBLIB_PIXELGRID_H
