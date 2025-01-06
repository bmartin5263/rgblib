//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_LEDBUFFER_H
#define RGBLIB_LEDBUFFER_H

#include "Point.h"
#include "Color.h"
#include "LEDChain.h"

template <u16 N>
class LEDBuffer final : public LEDChain {
public:

  auto operator[](u16 pixel) -> Color& override {
    return pixels[pixel];
  }

  auto operator[](Point point) -> Color& override {
    return pixels[(N * point.x) + point.y];
  }

  auto size() -> u16 override {
    return N;
  }

  auto head() -> Color* {
    return &pixels;
  }

private:
  Color pixels[N];

};

template <u16 N>
using LightStrip = LEDBuffer<N>;
template <u16 N>
using LightRing = LEDBuffer<N>;
template <u16 N>
using LightMatrix = LEDBuffer<N>;

#endif //RGBLIB_LEDBUFFER_H
