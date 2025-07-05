//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_TYPES_H
#define RGBLIB_TYPES_H

#include <optional>
#include <cstdint>
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

using milliseconds_t = u64;
using microseconds_t = u64;
using frames_t = u64;
using pin_num = i8;
using fahrenheit = float;
using percent = float;
using celsius = float;
using kph = float;
using mph = float;
using revs_per_minute = float;
using cstring = const char*;
using normal = float;
using time_t = u64;

template<typename V, class Self>
struct number_wrapper {
  using self_type = number_wrapper<V, Self>;

  V value;

  constexpr explicit number_wrapper(V value) : value(value) {}
  constexpr explicit number_wrapper(Self& wrapper) : value(wrapper.value) {}

  template<typename cast_to>
  constexpr auto to() const -> cast_to {
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
};

struct Duration : public number_wrapper<time_t, Duration> {
  constexpr explicit Duration() : number_wrapper<time_t, Duration>(0) {}
  constexpr explicit Duration(time_t microseconds) : number_wrapper<time_t, Duration>(microseconds) {}
  static constexpr auto Seconds(time_t amount) -> Duration { return Duration(amount * 1000000); }
  static constexpr auto Minutes(time_t amount) -> Duration { return Duration(amount * 60000000); }
  static constexpr auto Milliseconds(time_t amount) -> Duration { return Duration(amount * 1000); }
  static constexpr auto Microseconds(time_t amount) -> Duration { return Duration(amount); }
  static constexpr auto Max() -> Duration { return Duration(std::numeric_limits<time_t>::max()); }
  static constexpr auto Min() -> Duration { return Duration(0); }
  constexpr auto asSeconds() -> float { return static_cast<float>(value) / 1000000.f; }
  constexpr auto asMinutes() -> float { return static_cast<float>(value) / 60000000.f; }
  constexpr auto asMilliseconds() -> float { return static_cast<float>(value) / 1000.f; }
  constexpr auto asMicroseconds() -> float { return static_cast<float>(value); }
};

struct Timestamp : public number_wrapper<time_t, Timestamp> {
  constexpr explicit Timestamp() : number_wrapper<time_t, Timestamp>(0) {}
  constexpr explicit Timestamp(time_t microseconds) : number_wrapper<time_t, Timestamp>(microseconds) {}
  static constexpr auto OfMicroseconds(time_t amount) -> Timestamp { return Timestamp(amount); }
  constexpr auto asSeconds() -> float { return static_cast<float>(value) / 1000000.f; }
  constexpr auto asMinutes() -> float { return static_cast<float>(value) / 60000000.f; }
  constexpr auto asMilliseconds() -> float { return static_cast<float>(value) / 1000.f; }
  constexpr auto asMicroseconds() -> float { return static_cast<float>(value); }

  [[nodiscard]]
  constexpr auto percentOf(Timestamp rhs) const -> normal {
    return static_cast<float>(value) / static_cast<float>(rhs.value);
  }

  using number_wrapper::operator+;
  constexpr auto operator+(const Duration& rhs) const -> Timestamp {
    return Timestamp { value + rhs.value };
  }

  using number_wrapper::operator-;
  constexpr auto operator-(const Duration& rhs) const -> Timestamp {
    return Timestamp { value - rhs.value };
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

/**
 * static constexpr uint8_t D0         = 44; // also RX
 * static constexpr uint8_t D1         = 43; // also TX
 * static constexpr uint8_t D2         = 5;
 * static constexpr uint8_t D3         = 6;  // also CTS
 * static constexpr uint8_t D4         = 7;  // also DSR
 * static constexpr uint8_t D5         = 8;
 * static constexpr uint8_t D6         = 9;
 * static constexpr uint8_t D7         = 10;
 * static constexpr uint8_t D8         = 17;
 * static constexpr uint8_t D9         = 18;
 * static constexpr uint8_t D10        = 21; // also SS
 * static constexpr uint8_t D11        = 38; // also MOSI
 * static constexpr uint8_t D12        = 47; // also MISO
 * static constexpr uint8_t D13        = 48; // also SCK, LED_BUILTIN
 * static constexpr uint8_t LED_RED    = 46;
 * static constexpr uint8_t LED_GREEN  = 0;
 * static constexpr uint8_t LED_BLUE   = 45; // also RTS
 *
 * static constexpr uint8_t A0         = 1;  // also DTR
 * static constexpr uint8_t A1         = 2;
 * static constexpr uint8_t A2         = 3;
 * static constexpr uint8_t A3         = 4;
 * static constexpr uint8_t A4         = 11; // also SDA
 * static constexpr uint8_t A5         = 12; // also SCL
 * static constexpr uint8_t A6         = 13;
 * static constexpr uint8_t A7         = 14;
 */

constexpr auto D2_RGB = D5;
constexpr auto D3_RGB = D6;
constexpr auto D4_RGB = D7;

constexpr auto A4_RGB = 11;
constexpr auto A5_RGB = 12;
constexpr auto A6_RGB = 13;

}

#endif //RGBLIB_TYPES_H
