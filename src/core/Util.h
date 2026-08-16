//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_UTIL_H
#define RGBLIB_UTIL_H

#include <cmath>

namespace rgb {


constexpr auto ClampWrap(float value) {
  if (value < 0.0f) {
    return 0.0f;
  }
  if (value > 1.0f) {
    value = value - floorf(value);
  }
  return value;
}

template <typename T>
constexpr auto Clamp(T value, T minInclusive, T maxInclusive) {
  if (value < minInclusive) {
    return minInclusive;
  }
  else if (value > maxInclusive) {
    return maxInclusive;
  }
  else {
    return value;
  }
}

template<typename T, typename N>
constexpr auto Lerp(T a, T b, N t) -> T {
  static_assert(std::is_floating_point_v<N>, "Lerp t parameter must be floating point");
  return a + (b - a) * t;
}

/*
 * Wraps a value into the range [0.0, 1.0] by dropping its integer part,
 * preserving the fractional position for negative values as well
 * (e.g. -0.25 wraps to 0.75, not 0.0).
 */
constexpr auto WrapUnit(float value) -> float {
  if (value < 0.0f || value > 1.0f) {
    value = value - std::floor(value);
  }
  return value;
}

template<typename T, typename N>
constexpr auto LerpWrap(T a, T b, N t) -> T {
  static_assert(std::is_floating_point_v<N>, "LerpWrap t parameter must be floating point");
  return Lerp(a, b, WrapUnit(t));
}

template<typename T, typename N>
constexpr auto LerpClamp(T a, T b, N t) -> T {
  static_assert(std::is_floating_point_v<N>, "LerpClamp t parameter must be floating point");
  if (t <= 0.f) {
    return a;
  } else if (t >= 1.f) {
    return b;
  }
  return Lerp(a, b, t);
}

constexpr auto SinWave(float t, float frequency = .1f) -> float {
  return 1.0f * sinf(2.f * static_cast<float>(M_PI) * frequency * t);
}

/**
 * Returns a value between 0 and 1 in a sin wave pattern
 */
constexpr auto Pulse(Timestamp time, Duration period) -> normal {
  auto t = static_cast<float>(time.value % period.value) / static_cast<float>(period.value);
  return 0.5f * (1.0f + sinf(2.0f * static_cast<float>(M_PI) * t));
}

constexpr auto FloatToByte(normal f) -> u8 {
  constexpr u8 range = 255;
  if (f >= 1.0f) {
    return range;
  }
  if (f <= 0.0f) {
    return 0;
  }
  return static_cast<u8>((static_cast<u8>(f * static_cast<float>(range))) % (range + 1));
}

constexpr auto ByteToFloat(u8 byte) -> normal {
  return static_cast<float>(byte) / 255.0f;
}

constexpr auto ToMph(kph value) -> mph {
  return static_cast<mph>(static_cast<float>(value) * 0.621371f);
}

constexpr auto ToKph(mph value) -> kph {
  return static_cast<kph>(static_cast<float>(value) * 1.609344);
}

constexpr auto CToF(celsius value) -> fahrenheit {
  return (value * 9.0f / 5.0f) + 32.0f;
}

template<typename T>
constexpr auto EaseInOutElastic(T x) -> T {
  auto c5 = (2 * M_PI) / 4.5f;
  return x == 0 ? 0
      : x == 1 ? 1
      : x < 0.5f ? -(pow(2, 20 * x - 10) * sinf((20 * x - 11.125f) * c5)) / 2
      : (pow(2, -20 * x + 10) * sinf((20 * x - 11.125f) * c5)) / 2 + 1;
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
  return sqrtf(1.0f - powf(t - 1.0f, 2.0f));
}

constexpr auto EaseOutCubic(normal t) -> normal {
  return 1 - powf(1.0f - t, 3.0f);
}

constexpr auto EaseInOutExpo(normal t) -> normal {
  return t == 0.f
         ? 0.f
         : t == 1.f
           ? 1.f
           : t < 0.5f ? powf(2.f, 20.f * t - 10.f) / 2.f
                      : (2.f - powf(2.f, -20.f * t + 10.f)) / 2.f;
}

constexpr auto EaseInOutCubic(normal t) -> normal {
  return t < 0.5f ? 4.f * t * t * t : 1.f - powf(-2.f * t + 2.f, 3.f) / 2.f;
}

/*
 * Returns the percent value [0.0 to 1.0] that 'value' is between 'min' and 'max'
 */
template<typename T>
constexpr auto PercentBetween(T value, T min, T max) -> normal {
  auto diff = max - min;
  if (diff == 0.0f) {
    return 1.0f;
  }
  return (value - min) / diff;
}

template<typename T>
constexpr auto RunningAverage(T value, T next, float smoothingFactor) -> T {
  return static_cast<T>(smoothingFactor * static_cast<float>(next) + (1 - smoothingFactor) * static_cast<float>(value));
}

template<typename T, typename... Ts>
constexpr auto Max(T first, Ts... args) -> T {
  auto result = first;
  ((result = args > result ? args : result), ...);
  return result;
}

template<typename T, typename... Ts>
constexpr auto Min(T first, Ts... args) -> T {
  auto result = first;
  ((result = args < result ? args : result), ...);
  return result;
}

}

#endif //RGBLIB_UTIL_H