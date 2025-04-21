//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_UTIL_H
#define RGBLIB_UTIL_H

#include "Types.h"
#include "Assertions.h"

namespace rgb {

constexpr auto StaticAssertions() -> void {
  static_assert(sizeof(i32) > sizeof(u16));
  static_assert(sizeof(i64) > sizeof(u32));
  static_assert(sizeof(int) == 4);
  static_assert(sizeof(int) == sizeof(float));
  static_assert(sizeof(int*) == 4);
  static_assert(sizeof(long) == 4);
  static_assert(sizeof(long long) == 8);
  static_assert(sizeof(float) == 4);
  static_assert(sizeof(double) == 8);
}

constexpr float pi = PI;

constexpr auto ExtractBytes(u32 input, u8& byte0, u8& byte1, u8& byte2, u8& byte3) {
  // Extract each byte
  byte0 = (input & 0xFF);        // Extract the least significant byte
  byte1 = (input >> 8) & 0xFF;  // Extract the second byte
  byte2 = (input >> 16) & 0xFF; // Extract the third byte
  byte3 = (input >> 24) & 0xFF; // Extract the most significant byte
}

constexpr auto Clamp(float value) {
  if (value < 0.0f || value > 1.0f) {
    value = value - floor(value);
  }
  return value;
}

// Is this the right name?
constexpr auto Sigmoid(u32 t) -> float {
  return (sinf(static_cast<float>(t) * pi / 180) + 1);
}

template<typename T>
constexpr auto Lerp(T a, T b, normal t) -> T {
  return a + (b - a) * t;
}

template<typename T, typename R>
constexpr auto Lerp(T a, T b, R time, R range) -> T {
  return a + (b - a) * (static_cast<float>(time) / static_cast<float>(range));
}

template<typename T>
constexpr auto LerpWrap(T a, T b, normal t) -> T {
  if (t < 0.0f || t > 1.0f) {
    t = t - std::floor(t); // Wrap using the fractional part
  }
  return a + (b - a) * t;
}

template<typename T, typename R>
constexpr auto LerpWrap(T a, T b, R time, R range) -> T {
  auto t = static_cast<float>(time) / static_cast<float>(range);
  if (t < 0.0f || t > 1.0f) {
    t = t - std::floor(t); // Wrap using the fractional part
  }
  return a + (b - a) * t;
}

template<typename T>
constexpr auto LerpClamp(T a, T b, normal t) -> T {
  if (t <= 0.f) {
    return a;
  } else if (t >= 1.f) {
    return b;
  }
  return a + (b - a) * t;
}

template<typename T, typename R>
constexpr auto LerpClamp(T a, T b, R time, R range) -> T {
  auto t = static_cast<float>(time) / static_cast<float>(range);
  if (t <= 0.f) {
    return a;
  } else if (t >= 1.f) {
    return b;
  }
  return a + (b - a) * t;
}

constexpr auto SinWave(float t, float frequency = .1f) -> float {
  return 1.0f * sinf(2.f * pi * frequency * t);
}

constexpr auto Pulse(float time, float frequency = .1f) -> float {
  return 0.5f * (1 + sinf(2.f * pi * frequency * time));
}

constexpr auto FloatToByte(normal f) -> u8 {
  const u8 range = 255;
  return static_cast<u8>((static_cast<u8>(f * static_cast<float>(range))) % (range + 1));
}

constexpr auto ByteToFloat(u8 byte) -> normal {
  return static_cast<float>(byte) / 255.0f;
}

template<typename T>
constexpr auto easeInOutElastic(T x) -> T {
  auto c5 = (2 * PI) / 4.5f;
  return x == 0 ? 0
      : x == 1 ? 1
      : x < 0.5f ? -(pow(2, 20 * x - 10) * sinf((20 * x - 11.125f) * c5)) / 2
      : (pow(2, -20 * x + 10) * sinf((20 * x - 11.125f) * c5)) / 2 + 1;
}

constexpr auto KphToMph(kph value) -> mph {
  return static_cast<mph>(value * 0.621371f);
}

constexpr auto CToF(celsius value) -> fahrenheit {
  return (value * 9.0f / 5.0f) + 32.0f;
}

constexpr auto EaseOutBounce(normal t) -> normal {
  auto n1 = 7.5625f;
  auto d1 = 2.75f;

  if (t < 1.f / d1) {
    return n1 * t * t;
  } else if (t < 2.f / d1) {
    auto x = t -= 1.5f / d1;
    return n1 * x * t + 0.75f;
  } else if (t < 2.5 / d1) {
    auto x = t -= 2.25f / d1;
    return n1 * x * t + 0.9375f;
  } else {
    auto x = t -= 2.625f / d1;
    return n1 * x * t + 0.984375f;
  }
}

constexpr auto EaseInOutBounce(normal t) -> normal {
  return t < 0.5
         ? (1 - EaseOutBounce(1.f - 2.f * t)) / 2.f
         : (1 + EaseOutBounce(2.f * t - 1.f)) / 2.f;
}

constexpr auto EaseOutCirc(normal t) -> normal {
  return sqrt(1.0f - pow(t - 1.0f, 2.0f));
}

constexpr auto EaseOutCubic(normal t) -> normal {
  return 1 - pow(1.0f - t, 3.0f);
}

template<typename T>
constexpr auto RemapPercent(T min, T max, T actual) -> normal {
  auto diff = max - min;
  if (diff == 0.0f) {
    return 1.0f;
  }
  return (actual - min) / diff;
}
}

#endif //RGBLIB_UTIL_H