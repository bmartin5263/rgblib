//
// Created by Brandon on 12/25/24.
//

#include <math.h>
#include "Util.h"

void ExtractBytes(u32 input, u8& byte0, u8& byte1, u8& byte2, u8& byte3) {
  // Extract each byte
  byte0 = (input & 0xFF);        // Extract the least significant byte
  byte1 = (input >> 8) & 0xFF;  // Extract the second byte
  byte2 = (input >> 16) & 0xFF; // Extract the third byte
  byte3 = (input >> 24) & 0xFF; // Extract the most significant byte
}

float Clamp(float value) {
  if (value < 0.0f || value > 1.0f) {
    value = value - floor(value);
  }
  return value;
}

// Is this the right name?
auto Sigmoid(u32 t) -> float {
  return (sin(t * PI / 180) + 1) / 2;
}

auto Lerp(float a, float b, float t) -> float {
  return a + (b - a) * t;
}

auto LerpWrap(float a, float b, float t) -> float {
  if (t < 0.0f || t > 1.0f) {
    t = t - std::floor(t); // Wrap using the fractional part
  }
  return a + (b - a) * t;
}

auto LerpClamp(float a, float b, float t) -> float {
  if (t <= 0.f) {
    return a;
  }
  else if (t >= 1.f) {
    return b;
  }
  return a + (b - a) * t;
}