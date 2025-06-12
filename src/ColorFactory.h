//
// Created by Brandon on 6/12/25.
//

#ifndef RGBLIB_COLORFACTORY_H
#define RGBLIB_COLORFACTORY_H

#include "Color.h"

namespace rgb {

struct ColorFactory {
  constexpr static auto LEVEL_0 = 1 / 255.0f;
  constexpr static auto LEVEL_1 = .03f;

  float intensity{LEVEL_1};

  constexpr auto FromBytes(u8 r, u8 g, u8 b, u8 w = 0) -> Color {
    return Color{ByteToFloat(r), ByteToFloat(g), ByteToFloat(b), ByteToFloat(w)};
  }

  constexpr auto red() -> Color {
    return {intensity, 0, 0, 0};
  }

  constexpr auto orange() -> Color {
    return Color {1.0f, 0.2509803922f, 0, 0} * intensity;
  }

  constexpr auto salmon() -> Color {
    return Color {0.9765625f, 0.5019607843f, 0.4470588235f, 0.0f} * intensity;
  }

  constexpr auto gold() -> Color {
    return Color {1.0f, 0.5019607843f, 0.0f, 0.0f} * intensity;
  }

  constexpr auto maroon() -> Color {
    return Color {1.0f, 0.8431372549f, 0.0f, 0.0f} * intensity;
  }

  constexpr auto yellow() -> Color {
    return Color {intensity, intensity, 0.0f, 0.0f};
  }

  constexpr auto lime() -> Color {
    return Color {0.7490196078, 1.0f, 0.0f, 0.0f} * intensity;
  }

  constexpr auto springGreen() -> Color {
    return Color {0.0f, 1.0f, 0.4980392157f, 0.0f} * intensity;
  }

  constexpr auto green() -> Color {
    return Color {0.0f, intensity, 0.0f, 0.0f};
  }

  constexpr auto aquamarine() -> Color {
    return Color {0.4980392157f, 1.0f, 0.831372549, 0} * intensity;
  }

  constexpr auto cyan() -> Color {
    return Color {0.0f, intensity, intensity, 0.0f};
  }

  constexpr auto blue() -> Color {
    return Color {0.0f, 0.0f, intensity, 0.0f};
  }

  constexpr auto purple() -> Color {
    return Color {0.5019607843f, 0.0f, 1.0f, 0.0f} * intensity;
  }

  constexpr auto indigo() -> Color {
    return Color {0.2941176471f, 0, 0.5098039216f, 0} * intensity;
  }

  constexpr auto magenta() -> Color {
    return Color {intensity, 0.0f, intensity, 0.0f};
  }

  constexpr auto white() -> Color {
    return Color {intensity, intensity, intensity, 0.0f};
  }

  constexpr auto trueWhite() -> Color {
    return Color {0.0f, 0.0f, 0.0f, intensity};
  }
};

}

#endif //RGBLIB_COLORFACTORY_H
