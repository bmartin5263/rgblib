//
// Created by Brandon on 1/5/25.
//

#include "Color.h"

Color::Color(): r(0.f), g(0.f), b(0.f), w(0.f) {

}

Color::Color(float w): r(0.f), g(0.f), b(0.f), w(w) {

}

Color::Color(float r, float g, float b): r(r), g(g), b(b), w(0.f) {

}

Color::Color(float r, float g, float b, float w): r(r), g(g), b(b), w(w) {

}


auto Color::RED() -> const Color& {
  static Color c{1.0f, 0, 0, 0};
  return c;
}

auto Color::RED(float intensity) -> Color {
  return {intensity, 0, 0, 0};
}

auto Color::ORANGE() -> const Color& {
  static Color c{1.0f, 64, 0, 0};
  return c;
}

auto Color::SALMON() -> const Color& {
  static Color c{250, 128, 114, 0};
  return c;
}

auto Color::GOLD() -> const Color& {
  static Color c{1.0f, 128, 0, 0};
  return c;
}

auto Color::MAROON() -> const Color& {
  static Color c{1.0f, 215, 0, 0};
  return c;
}

auto Color::YELLOW(float intensity) -> Color {
  return {intensity, intensity, 0, 0};
}

auto Color::YELLOW() -> const Color& {
  static Color c{1.0f, 1.0f, 0, 0};
  return c;
}

auto Color::LIME() -> const Color& {
  static Color c{191, 1.0f, 0, 0};
  return c;
}

auto Color::SPRING_GREEN() -> const Color& {
  static Color c{0, 1.0f, 127, 0};
  return c;
}

auto Color::GREEN() -> const Color& {
  static Color c{0, 1.0f, 0, 0};
  return c;
}

auto Color::GREEN(float intensity) -> Color {
  return {0, intensity, 0, 0};
}

auto Color::AQUAMARINE() -> const Color& {
  static Color c{127, 1.0f, 212, 0};
  return c;
}

auto Color::CYAN() -> const Color& {
  static Color c{0, 1.0f, 1.0f, 0};
  return c;
}

auto Color::CYAN(float intensity) -> Color {
  return {0, intensity, intensity, 0};
}

auto Color::BLUE() -> const Color& {
  static Color c{0, 0, 1.0f, 0};
  return c;
}

auto Color::BLUE(float intensity) -> Color {
  return {0, 0, intensity, 0};
}

auto Color::PURPLE() -> const Color& {
  static Color c{106, 13, 173, 0};
  return c;
}

auto Color::VIOLET() -> const Color& {
  static Color c{128, 0, 1.0f, 0};
  return c;
}

auto Color::INDIGO() -> const Color& {
  static Color c{75, 0, 130, 0};
  return c;
}

auto Color::MAGENTA() -> const Color& {
  static Color c{1.0f, 0, 1.0f, 0};
  return c;
}

auto Color::MAGENTA(float intensity) -> Color {
  return {intensity, 0, intensity, 0};
}

auto Color::WHITE(float intensity) -> Color {
  return {0, 0, 0, intensity};
}

auto Color::OFF() -> const Color& {
  static Color c{0, 0, 0, 0};
  return c;
}

auto Color::HueToRgb(float p, float q, float t) -> float {
  if (t < 0) t += 1;
  if (t > 1) t -= 1;
  if (t < 1.0f / 6) return p + (q - p) * 6 * t;
  if (t < 1.0f / 2) return q;
  if (t < 2.0f / 3) return p + (q - p) * (2.0f / 3 - t) * 6;
  return p;
}

auto Color::HslToRgb(float h, float s, float l) -> Color {
  float r, g, b;

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