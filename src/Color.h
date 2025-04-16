//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_COLOR_H
#define RGBLIB_COLOR_H

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

  constexpr auto operator*=(float rhs) -> Color& {
    r *= rhs;
    g *= rhs;
    b *= rhs;
    w *= rhs;
    return *this;
  }

  constexpr auto operator*(float rhs) const -> Color {
    return Color { r * rhs, g * rhs, b * rhs, w * rhs };
  }

  constexpr auto lerp(const Color& to, float time) -> Color {
    return Color { Lerp(r, to.r, time), Lerp(g, to.g, time), Lerp(b, to.b, time), Lerp(w, to.w, time) };
  }

  constexpr auto lerpWrap(const Color& to, float time) -> Color {
    return Color { LerpWrap(r, to.r, time), LerpWrap(g, to.g, time), LerpWrap(b, to.b, time), LerpWrap(w, to.w, time) };
  }

  constexpr auto lerpClamp(const Color& to, float time) -> Color {
    return Color { LerpClamp(r, to.r, time), LerpClamp(g, to.g, time), LerpClamp(b, to.b, time), LerpClamp(w, to.w, time) };
  }

  static constexpr auto FromBytes(u8 r, u8 g, u8 b, u8 w = 0) -> Color {
    return Color{ByteToFloat(r), ByteToFloat(g), ByteToFloat(b), ByteToFloat(w)};
  }

  static constexpr auto RED(float intensity = 1.0f) -> Color {
    return {intensity, 0, 0, 0};
  }

  static constexpr auto ORANGE() -> Color {
    return {1.0f, 0.2509803922f, 0, 0};
  }

  static constexpr auto SALMON() -> Color {
    return {250, 0.5019607843f, 0.4470588235f, 0};
  }

  static constexpr auto GOLD() -> Color {
    return {1.0f, 0.5019607843f, 0, 0};
  }

  static constexpr auto MAROON() -> Color {
    return {1.0f, 0.8431372549f, 0, 0};
  }

  static constexpr auto YELLOW(float intensity = 1.0f) -> Color {
    return {intensity, intensity, 0, 0};
  }

  static constexpr auto LIME() -> Color {
    return {0.7490196078, 1.0f, 0, 0};
  }

  static constexpr auto SPRING_GREEN() -> Color {
    return {0, 1.0f, 0.4980392157f, 0};
  }

  static constexpr auto GREEN(int intensity) = delete;

  static constexpr auto GREEN(float intensity = 1.0f) -> Color {
    return {0, intensity, 0, 0};
  }

  static constexpr auto AQUAMARINE() -> Color {
    return {0.4980392157f, 1.0f, 0.831372549, 0};
  }

  static constexpr auto CYAN(float intensity = 1.0f) -> Color {
    return {0, intensity, intensity, 0};
  }

  static constexpr auto BLUE(float intensity = 1.0f) -> Color {
    return {0, 0, intensity, 0};
  }

  static constexpr auto PURPLE() -> Color {
    return {0.4156862745f, 0.05098039216f, 0.6784313725f, 0};
  }

  static constexpr auto VIOLET() -> Color {
    return {0.5019607843f, 0, 1.0f, 0};
  }

  static constexpr auto INDIGO() -> Color {
    return {0.2941176471f, 0, 0.5098039216f, 0};
  }

  static constexpr auto MAGENTA(float intensity = 1.0f) -> Color {
    return {intensity, 0, intensity, 0};
  }

  static constexpr auto WHITE(float intensity = 1.0) -> Color {
    return {0, 0, 0, intensity};
  }

  static constexpr auto OFF() -> Color {
    return {0.f, 0.f, 0.f, 0.f};
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


#endif //RGBLIB_COLOR_H
