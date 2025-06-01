//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_POINT_H
#define RGBLIB_POINT_H

#include "Types.h"

namespace rgb {

struct Point {

  [[nodiscard]] constexpr auto flatten(u16 columns) const -> size_t {
    return (y * columns) + x;
  }

  constexpr auto operator+(const Point& rhs) const -> Point {
    return { x + rhs.x, y + rhs.y };
  }

  constexpr auto operator+=(const Point& rhs) -> Point& {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  constexpr auto operator-(const Point& rhs) const -> Point {
    return { x - rhs.x, y - rhs.y };
  }

  constexpr auto operator-=(const Point& rhs) -> Point& {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  constexpr auto operator*(const Point& rhs) const -> Point {
    return { x * rhs.x, y * rhs.y };
  }

  constexpr auto operator*=(const Point& rhs) -> Point& {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }

  constexpr auto operator/(const Point& rhs) const -> Point {
    return { x / rhs.x, y / rhs.y };
  }

  constexpr auto operator/=(const Point& rhs) -> Point& {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }

  constexpr friend auto operator==(const Point& lhs, const Point& rhs) -> bool {
    return lhs.x == rhs.x
        && lhs.y == rhs.y;
  }

  constexpr friend auto operator!=(const Point& lhs, const Point& rhs) -> bool {
    return !(lhs == rhs);
  }

  int x{};
  int y{};
};


}

#endif //RGBLIB_POINT_H
