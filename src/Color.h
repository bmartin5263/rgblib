//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_COLOR_H
#define RGBLIB_COLOR_H


namespace rgb {

struct Color {
  float r, g, b, w;

  constexpr Color(): r(0.f), g(0.f), b(0.f), w(0.f) {

  }

  constexpr Color(float w): r(0.f), g(0.f), b(0.f), w(w) {

  }

  constexpr Color(float r, float g, float b): r(r), g(g), b(b), w(0.f) {

  }

  constexpr Color(float r, float g, float b, float w): r(r), g(g), b(b), w(w) {

  }

  static constexpr auto RED() -> Color {
    return {1.0f, 0, 0, 0};
  }

  static constexpr auto RED(float intensity) -> Color {
    return {intensity, 0, 0, 0};
  }

  static constexpr auto ORANGE() -> Color {
    return {1.0f, 64, 0, 0};
  }

  static constexpr auto SALMON() -> Color {
    return {250, 128, 114, 0};
  }

  static constexpr auto GOLD() -> Color {
    return {1.0f, 128, 0, 0};
  }

  static constexpr auto MAROON() -> Color {
    return {1.0f, 215, 0, 0};
  }

  static constexpr auto YELLOW(float intensity) -> Color {
    return {intensity, intensity, 0, 0};
  }

  static constexpr auto YELLOW() -> Color {
    return {1.0f, 1.0f, 0, 0};
  }

  static constexpr auto LIME() -> Color {
    return {191, 1.0f, 0, 0};
  }

  static constexpr auto SPRING_GREEN() -> Color {
    return {0, 1.0f, 127, 0};
  }

  static constexpr auto GREEN() -> Color {
    return {0, 1.0f, 0, 0};
  }

  static constexpr auto GREEN(float intensity) -> Color {
    return {0, intensity, 0, 0};
  }

  static constexpr auto AQUAMARINE() -> Color {
    return {127, 1.0f, 212, 0};
  }

  static constexpr auto CYAN() -> Color {
    return {0, 1.0f, 1.0f, 0};
  }

  static constexpr auto CYAN(float intensity) -> Color {
    return {0, intensity, intensity, 0};
  }

  static constexpr auto BLUE() -> Color {
    return {0, 0, 1.0f, 0};
  }

  static constexpr auto BLUE(float intensity) -> Color {
    return {0, 0, intensity, 0};
  }

  static constexpr auto PURPLE() -> Color {
    return {106, 13, 173, 0};
  }

  static constexpr auto VIOLET() -> Color {
    return {128, 0, 1.0f, 0};
  }

  static constexpr auto INDIGO() -> Color {
    return {75, 0, 130, 0};
  }

  static constexpr auto MAGENTA() -> Color {
    return {1.0f, 0, 1.0f, 0};
  }

  static constexpr auto MAGENTA(float intensity) -> Color {
    return {intensity, 0, intensity, 0};
  }

  static constexpr auto WHITE(float intensity) -> Color {
    return {0, 0, 0, intensity};
  }

  static constexpr auto OFF() -> Color {
    return {0, 0, 0, 0};
  }

  static constexpr auto HueToRgb(float p, float q, float t) -> float {
    if (t < 0) t += 1;
    if (t > 1) t -= 1;
    if (t < 1.0f / 6) return p + (q - p) * 6 * t;
    if (t < 1.0f / 2) return q;
    if (t < 2.0f / 3) return p + (q - p) * (2.0f / 3 - t) * 6;
    return p;
  }

private:
  static constexpr auto HslToRgb(float h, float s, float l) -> Color {
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
};

}


#endif //RGBLIB_COLOR_H
