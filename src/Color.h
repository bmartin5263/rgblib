//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_COLOR_H
#define RGBLIB_COLOR_H


struct Color {
  Color();
  Color(float w);
  Color(float r, float g, float b);
  Color(float r, float g, float b, float w);

  bool operator==(const Color& rhs) const;
  bool operator!=(const Color& rhs) const;

  float r, g, b, w;

  static auto RED() -> const Color&;
  static auto RED(float intensity) -> Color;
  static auto MAROON() -> const Color&;
  static auto SALMON() -> const Color&;

  static auto ORANGE() -> const Color&;
  static auto GOLD() -> const Color&;
  static auto YELLOW() -> const Color&;
  static auto YELLOW(float intensity) -> Color;

  static auto LIME() -> const Color&;
  static auto SPRING_GREEN() -> const Color&;
  static auto GREEN() -> const Color&;
  static auto GREEN(float intensity) -> Color;

  static auto AQUAMARINE() -> const Color&;
  static auto CYAN() -> const Color&;
  static auto CYAN(float intensity) -> Color;
  static auto BLUE() -> const Color&;
  static auto BLUE(float intensity) -> Color;

  static auto PURPLE() -> const Color&;
  static auto VIOLET() -> const Color&;
  static auto INDIGO() -> const Color&;
  static auto MAGENTA() -> const Color&;
  static auto MAGENTA(float intensity) -> Color;

  static auto WHITE() -> const Color&;
  static auto WHITE(float intensity) -> Color;
  static auto OFF() -> const Color&;

  static auto HslToRgb(float h, float s = 1.0f, float l = .5f) -> Color;

private:
  static auto HueToRgb(float p, float q, float t) -> float;
};


#endif //RGBLIB_COLOR_H
