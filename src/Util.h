//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_UTIL_H
#define RGBLIB_UTIL_H

#include "Types.h"
#include "Assertions.h"

#define MAX(a, b) \
    ({ auto _a = (a); auto _b = (b); _a > _b ? _a : _b; })

#define MIN(a, b) \
    ({ auto _a = (a); auto _b = (b); _a < _b ? _a : _b; })

constexpr void ExtractBytes(u32 input, u8& byte0, u8& byte1, u8& byte2, u8& byte3) {
  // Extract each byte
  byte0 = (input & 0xFF);        // Extract the least significant byte
  byte1 = (input >> 8) & 0xFF;  // Extract the second byte
  byte2 = (input >> 16) & 0xFF; // Extract the third byte
  byte3 = (input >> 24) & 0xFF; // Extract the most significant byte
}

constexpr float Clamp(float value) {
  if (value < 0.0f || value > 1.0f) {
    value = value - floor(value);
  }
  return value;
}

// Is this the right name?
constexpr auto Sigmoid(u32 t) -> float {
  return (sinf(static_cast<float>(t) * static_cast<float>(PI) / 180) + 1) / 2;
}

constexpr auto Lerp(float a, float b, float t) {
  return a + (b - a) * t;
}

constexpr auto LerpWrap(float a, float b, float t) {
  if (t < 0.0f || t > 1.0f) {
    t = t - std::floor(t); // Wrap using the fractional part
  }
  return a + (b - a) * t;
}

constexpr auto LerpClamp(float a, float b, float t) {
  if (t <= 0.f) {
    return a;
  }
  else if (t >= 1.f) {
    return b;
  }
  return a + (b - a) * t;
}

#endif //RGBLIB_UTIL_H
