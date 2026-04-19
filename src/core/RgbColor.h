//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_RGBCOLOR_H
#define RGBLIB_RGBCOLOR_H

#include <esp_random.h>
#include <type_traits>
#include "Types.h"
#include "Util.h"

namespace rgb {

struct Color {
  float r, g, b, w;

  constexpr Color(): r(0.f), g(0.f), b(0.f), w(0.f) {

  }

  explicit constexpr Color(float w): r(0.f), g(0.f), b(0.f), w(w) {

  }

  constexpr Color(float r, float g, float b): r(r), g(g), b(b), w(0.f) {

  }

  constexpr Color(float r, float g, float b, float w): r(r), g(g), b(b), w(w) {

  }

  constexpr auto operator*(float rhs) const -> Color {
    return { r * rhs, g * rhs, b * rhs, w * rhs };
  }

  constexpr auto operator*=(float rhs) -> Color& {
    r *= rhs;
    g *= rhs;
    b *= rhs;
    w *= rhs;
    return *this;
  }

  constexpr auto operator+(const Color& rhs) const -> Color {
    return { r + rhs.r, g + rhs.g, b + rhs.b, w + rhs.w };
  }

  constexpr auto operator+=(const Color& rhs) -> Color& {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    w += rhs.w;
    return *this;
  }

  constexpr auto operator-(const Color& rhs) const -> Color {
    return { r - rhs.r, g - rhs.g, b - rhs.b, w - rhs.w };
  }

  constexpr auto operator-=(const Color& rhs) -> Color& {
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    w -= rhs.w;
    return *this;
  }

  constexpr auto operator*(const Color& rhs) const -> Color {
    return { r * rhs.r, g * rhs.g, b * rhs.b, w * rhs.w };
  }

  constexpr auto operator*=(const Color& rhs) -> Color& {
    r *= rhs.r;
    g *= rhs.g;
    b *= rhs.b;
    w *= rhs.w;
    return *this;
  }

  constexpr auto operator/(const Color& rhs) const -> Color {
    return { r / rhs.r, g / rhs.g, b / rhs.b, w / rhs.w };
  }

  constexpr auto operator/=(const Color& rhs) -> Color& {
    r /= rhs.r;
    g /= rhs.g;
    b /= rhs.b;
    w /= rhs.w;
    return *this;
  }

  constexpr friend auto operator==(const Color& lhs, const Color& rhs) -> bool {
    return lhs.r == rhs.r
        && lhs.g == rhs.g
        && lhs.b == rhs.b
        && lhs.w == rhs.w;
  }

  constexpr friend auto operator!=(const Color& lhs, const Color& rhs) -> bool {
    return !(lhs == rhs);
  }

  template<typename T>
  [[nodiscard]]
  constexpr auto lerp(const Color& to, T time) const -> Color {
    static_assert(std::is_floating_point_v<T>, "lerp time parameter must be floating point");
    return Color { Lerp(r, to.r, time), Lerp(g, to.g, time), Lerp(b, to.b, time), Lerp(w, to.w, time) };
  }

  template<typename T>
  [[nodiscard]]
  constexpr auto lerpWrap(const Color& to, T time) const -> Color {
    static_assert(std::is_floating_point_v<T>, "lerpWrap time parameter must be floating point");
    return Color { LerpWrap(r, to.r, time), LerpWrap(g, to.g, time), LerpWrap(b, to.b, time), LerpWrap(w, to.w, time) };
  }

  template<typename T>
  [[nodiscard]]
  constexpr auto lerpClamp(const Color& to, T time) const -> Color {
    static_assert(std::is_floating_point_v<T>, "lerpClamp time parameter must be floating point");
    return Color { LerpClamp(r, to.r, time), LerpClamp(g, to.g, time), LerpClamp(b, to.b, time), LerpClamp(w, to.w, time) };
  }

  static constexpr auto FromBytes(u8 r, u8 g, u8 b, u8 w = 0) -> Color {
    return Color{ByteToFloat(r), ByteToFloat(g), ByteToFloat(b), ByteToFloat(w)};
  }

  static constexpr auto RED() -> Color {
    return {1.0f, 0, 0, 0};
  }

  static constexpr auto ORANGE() -> Color {
    return Color {1.0f, .5f, 0.f, 0.f};
  }

  static constexpr auto YELLOW() -> Color {
    return Color {1.0f, 1.0f, 0.f, 0.f};
  }

  static constexpr auto LIME() -> Color {
    return Color {.5f, 1.0f, 0.f, 0.f};
  }

  static constexpr auto GREEN() -> Color {
    return Color {0, 1.0f, 0, 0};
  }

  static constexpr auto SPRING_GREEN() -> Color {
    return Color {0, 1.0f, .5f, 0};
  }

  static constexpr auto CYAN() -> Color {
    return Color {0, 1.0f, 1.0f, 0};
  }

  static constexpr auto SKY_BLUE() -> Color {
    return Color {0, .5f, 1.0f, 0};
  }

  static constexpr auto BLUE() -> Color {
    return Color {0, 0, 1.0f, 0};
  }

  static constexpr auto PURPLE() -> Color {
    return Color {.5f, 0, 1.0f, 0};
  }

  static constexpr auto MAGENTA() -> Color {
    return Color {1.0f, 0, 1.0f, 0};
  }

  static constexpr auto PINK() -> Color {
    return Color {1.0f, 0.0f, .5f, 0};
  }

  static constexpr auto WHITE() -> Color {
    return FAKE_WHITE();
  }

  static constexpr auto FAKE_WHITE() -> Color {
    return Color {1.0f, 1.0f, 1.0f, 0.f};
  }

  static constexpr auto REAL_WHITE() -> Color {
    return Color {0.f, 0.f, 0.f, 1.0f};
  }

  static constexpr auto OFF() -> Color {
    return {0.f, 0.f, 0.f, 0.f};
  }

  static auto Random12(uint32_t seed = esp_random()) -> Color {
    return Sequential12(seed);
  }

  static constexpr auto Sequential12(uint32_t index) -> Color {
    switch (index % 12) {
      case 0: return RED();
      case 1: return ORANGE();
      case 2: return YELLOW();
      case 3: return LIME();
      case 4: return GREEN();
      case 5: return SPRING_GREEN();
      case 6: return CYAN();
      case 7: return SKY_BLUE();
      case 8: return BLUE();
      case 9: return PURPLE();
      case 10: return MAGENTA();
      default: return PINK();
    }
  }

  static constexpr auto HslToRgb(float h, float s = 1.0f, float l = .5f) -> Color {
    float r{}, g{}, b{};

    if (s == 0.f) {
      // Achromatic (gray)
      r = g = b = l;
    } else {
      float q = l < 0.5f ? l * (1 + s) : l + s - l * s;
      float p = 2 * l - q;
      r = HueToRgb(p, q, h + 1.0f / 3);
      g = HueToRgb(p, q, h);
      b = HueToRgb(p, q, h - 1.0f / 3);
    }

    // Convert to 0-1.0f range
    return {r, g, b};
  }

private:

  static constexpr auto HueToRgb(float p, float q, float t) -> float {
    if (t < 0) t += 1;
    if (t > 1) t -= 1;
    if (t < 1.0f / 6) return p + (q - p) * 6 * t;
    if (t < 1.0f / 2) return q;
    if (t < 2.0f / 3) return p + (q - p) * (2.0f / 3 - t) * 6;
    return p;
  }
};

}


#endif //RGBLIB_RGBCOLOR_H
