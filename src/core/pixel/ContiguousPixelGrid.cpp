//
// Created by Brandon on 4/19/26.
//

#include "ContiguousPixelGrid.h"
#include "Assertions.h"

namespace rgb {

auto ContiguousPixelGrid::get(uint pixel) const -> Pixel {
  ASSERT(pixel < length(), "Pixel is out of bounds");
  return data()[pixel];
}

auto ContiguousPixelGrid::set(uint pixel, const Color& color) -> void {
  ASSERT(pixel < length(), "Pixel is out of bounds");
  data()[pixel] = color;
}

auto ContiguousPixelGrid::get(uint column, uint row) const -> Pixel {
  ASSERT(column < columns(), "Column is out of bounds");
  ASSERT(row < rows(), "Row is out of bounds");
  return data()[row * columns() + column];
}

auto ContiguousPixelGrid::get(Point position) const -> Pixel {
  ASSERT(position.x < columns(), "Column is out of bounds");
  ASSERT(position.y < rows(), "Row is out of bounds");
  return data()[position.flatten(columns())];
}

auto ContiguousPixelGrid::set(uint column, uint row, const Color& color) -> void {
  ASSERT(column < columns(), "Column is out of bounds");
  ASSERT(row < rows(), "Row is out of bounds");
  data()[row * columns() + column] = color;
}

auto ContiguousPixelGrid::set(Point position, const Color& color) -> void {
  ASSERT(position.x < columns(), "Column is out of bounds");
  ASSERT(position.y < rows(), "Row is out of bounds");
  data()[position.flatten(columns())] = color;
}

}
