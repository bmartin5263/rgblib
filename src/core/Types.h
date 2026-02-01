//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_TYPES_H
#define RGBLIB_TYPES_H

#include <cstdint>
#include <limits>
#include <pins_arduino.h>

namespace rgb {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using byte = u8;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using uint = unsigned int;

using milliseconds_t = u64;
using microseconds_t = u64;
using frames_t = u64;
using fahrenheit = float;
using percent = float;
using celsius = float;
using kph = uint;
using mph = uint;
using revs_per_minute = uint;
using cstring = const char*;
using normal = float; // a float value typically between 0.0 and 1.0
using time_t = u64;

template<typename V, class Self>
struct number_wrapper {
  using self_type = number_wrapper<V, Self>;

  V value;

  constexpr explicit number_wrapper(V value) : value(value) {}
  constexpr explicit number_wrapper(Self& wrapper) : value(wrapper.value) {}

  template<typename cast_to>
  constexpr auto as() const -> cast_to {
    return static_cast<cast_to>(value);
  }

  constexpr auto operator=(V rhs) -> self_type& {
    value = rhs;
    return *this;
  }

  constexpr auto operator+(const Self& rhs) const -> Self {
    return Self { value + rhs.value };
  }

  constexpr auto operator-(const Self& rhs) const -> Self {
    return Self { value - rhs.value };
  }

  constexpr auto operator*(const Self& rhs) const -> Self {
    return Self { value * rhs.value };
  }

  constexpr auto operator/(const Self& rhs) const -> Self {
    return Self { value / rhs.value };
  }

  constexpr auto operator%(const Self& rhs) const -> Self {
    return Self { value % rhs.value };
  }

  constexpr auto operator+=(const Self& rhs) -> Self& {
    value += rhs.value;
    return static_cast<Self&>(*this);
  }

  constexpr auto operator-=(const Self& rhs) -> Self& {
    value -= rhs.value;
    return static_cast<Self&>(*this);
  }

  constexpr auto operator*=(const Self& rhs) -> Self& {
    value *= rhs.value;
    return static_cast<Self&>(*this);
  }

  constexpr auto operator/=(const Self& rhs) -> Self& {
    value /= rhs.value;
    return static_cast<Self&>(*this);
  }

  constexpr auto operator%=(const Self& rhs) -> Self& {
    value %= rhs.value;
    return static_cast<Self&>(*this);
  }

  constexpr friend auto operator==(self_type lhs, self_type rhs) -> bool {
    return lhs.value == rhs.value;
  }

  constexpr friend auto operator!=(self_type lhs, self_type rhs) -> bool {
    return lhs.value != rhs.value;
  }

  constexpr friend auto operator<(self_type lhs, self_type rhs) -> bool {
    return lhs.value < rhs.value;
  }

  constexpr friend auto operator>(self_type lhs, self_type rhs) -> bool {
    return lhs.value > rhs.value;
  }

  constexpr friend auto operator<=(self_type lhs, self_type rhs) -> bool {
    return lhs.value <= rhs.value;
  }

  constexpr friend auto operator>=(self_type lhs, self_type rhs) -> bool {
    return lhs.value >= rhs.value;
  }

  constexpr auto operator++() -> Self& {
    ++value;
    return static_cast<Self&>(*this);
  }

  constexpr auto operator++(int) -> Self {
    Self& me = static_cast<Self&>(*this);
    Self tmp(me);
    operator++();
    return tmp;
  }

  [[nodiscard]]
  constexpr auto isZero() const -> bool {
    return value == 0;
  }
};

struct Duration : public number_wrapper<time_t, Duration> {
  constexpr explicit Duration() : number_wrapper<time_t, Duration>(0) {}
  constexpr explicit Duration(time_t milliseconds) : number_wrapper<time_t, Duration>(milliseconds) {}
  static constexpr auto Seconds(time_t amount) -> Duration { return Duration(amount * 1000000); }
  static constexpr auto Minutes(time_t amount) -> Duration { return Duration(amount * 60000000); }
  static constexpr auto Milliseconds(time_t amount) -> Duration { return Duration(amount * 1000); }
  static constexpr auto Microseconds(time_t amount) -> Duration { return Duration(amount); }
  static constexpr auto Max() -> Duration { return Duration(std::numeric_limits<time_t>::max()); }
  static constexpr auto Zero() -> Duration { return Duration(0); }
  static constexpr auto Immediately() -> Duration { return Duration(0); }
  [[nodiscard]] constexpr auto asSeconds() const -> time_t { return value / 1000000; }
  [[nodiscard]] constexpr auto asMinutes() const -> time_t { return value / 60000000; }
  [[nodiscard]] constexpr auto asMilliseconds() const -> time_t { return value / 1000; }
  [[nodiscard]] constexpr auto asMicroseconds() const -> time_t { return value; }
};

struct Timestamp : public number_wrapper<time_t, Timestamp> {
  constexpr explicit Timestamp() : number_wrapper<time_t, Timestamp>(0) {}
  constexpr explicit Timestamp(time_t microseconds) : number_wrapper<time_t, Timestamp>(microseconds) {}
  static constexpr auto Microseconds(time_t amount) -> Timestamp { return Timestamp(amount); }
  static constexpr auto Milliseconds(time_t amount) -> Timestamp { return Timestamp(amount * 1000); }
  static constexpr auto Max() -> Timestamp { return Timestamp(std::numeric_limits<time_t>::max()); }
  static constexpr auto Zero() -> Timestamp { return Timestamp(0); }
  constexpr auto asSeconds() -> time_t { return value / 1000000; }
  constexpr auto asMinutes() -> time_t { return value / 60000000; }
  constexpr auto asMilliseconds() -> time_t { return value / 1000; }
  constexpr auto asMicroseconds() -> time_t { return value; }

  [[nodiscard]]
  constexpr auto percentOf(Timestamp rhs) const -> normal {
    return static_cast<float>(value) / static_cast<float>(rhs.value);
  }

  [[nodiscard]]
  constexpr auto percentOf(Duration rhs) const -> normal {
    return static_cast<float>(value % rhs.value) / static_cast<float>(rhs.value);
  }

  using number_wrapper::operator+;
  constexpr auto operator+(const Duration& rhs) const -> Timestamp {
    return Timestamp { value + rhs.value };
  }

  using number_wrapper::operator-;
  constexpr auto operator-(const Duration& rhs) const -> Timestamp {
    return Timestamp { value - rhs.value };
  }

  using number_wrapper::operator*;
  constexpr auto operator*(const Duration& rhs) const -> Timestamp {
    return Timestamp { value * rhs.value };
  }

  using number_wrapper::operator/;
  constexpr auto operator/(const Duration& rhs) const -> Timestamp {
    return Timestamp { value / rhs.value };
  }

  using number_wrapper::operator+=;
  constexpr auto operator+=(const Duration& rhs) -> Timestamp& {
    value += rhs.value;
    return static_cast<Timestamp&>(*this);
  }

  using number_wrapper::operator-=;
  constexpr auto operator-=(const Duration& rhs) -> Timestamp& {
    value -= rhs.value;
    return *this;
  }

  using number_wrapper::operator%;
  constexpr auto operator%(const Duration& rhs) const -> Timestamp {
    return Timestamp { value % rhs.value };
  }

  [[nodiscard]]
  constexpr auto mod(const Duration& rhs) const -> Timestamp {
    return Timestamp { value % rhs.value };
  }

  using number_wrapper::operator%=;
  constexpr auto operator%=(const Duration& rhs) -> Timestamp& {
    value %= rhs.value;
    return static_cast<Timestamp&>(*this);
  }

  using number_wrapper::operator*=;
  constexpr auto operator*=(const Duration& rhs) -> Timestamp& {
    value *= rhs.value;
    return *this;
  }

  using number_wrapper::operator/=;
  constexpr auto operator/=(const Duration& rhs) -> Timestamp& {
    value /= rhs.value;
    return *this;
  }

  constexpr auto timeSince(const Timestamp& earlierTime) -> Duration {
    return Duration { value - earlierTime.value };
  }
};

constexpr auto D2_RGB = D5;
constexpr auto D3_RGB = D6;
constexpr auto D4_RGB = D7;
constexpr auto D5_RGB = D8;
constexpr auto D6_RGB = D9;

constexpr auto A4_RGB = 11;
constexpr auto A5_RGB = 12;
constexpr auto A6_RGB = 13;

}

#endif //RGBLIB_TYPES_H
