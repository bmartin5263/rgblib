//
// Created by Brandon on 1/5/25.
//

#include "Assertions.h"
#include "PixelGrid.h"
#include "PixelSlice.h"
#include "Color.h"
#include "Point.h"

namespace rgb {


auto PixelGrid::get(Point point) -> Pixel* {
  auto columns = getColumns();
  auto rows = getSize() / columns;
  ASSERT(point.x >= 0, "Point.X is negative");
  ASSERT(point.y >= 0, "Pixel.Y is negative");
  ASSERT(point.x < columns, "Pixel.X is out of bounds");
  ASSERT(point.y < rows, "Pixel.Y is out of bounds");
  return getHead() + ((point.y * columns) + point.x);
}

auto PixelGrid::set(Point point, const Color& color) -> void {
  *get(point) = color;
}


auto PixelGrid::operator[](Point point) -> Color& {
  return *get(point);
}

}