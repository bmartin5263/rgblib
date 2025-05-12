//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_TYPES_H
#define RGBLIB_TYPES_H

#include <optional>
#include <cstdint>

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

using milliseconds_t = unsigned long;
using microseconds_t = unsigned long;
using frames_t = unsigned long;
using pin_num = i8;
using fahrenheit = float;
using percent = float;
using celsius = float;
using kph = float;
using mph = float;
using revs_per_minute = float;
using cstring = const char*;
using normal = float;

template<typename V, class Self>
struct number_wrapper {
  using self_type = number_wrapper<V, Self>;
  
  V value;

  constexpr explicit number_wrapper(V value) : value(value) {}
  constexpr explicit number_wrapper(Self& wrapper) : value(wrapper.value) {}

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
    return *this;
  }

  constexpr auto operator*=(const Self& rhs) -> Self& {
    value *= rhs.value;
    return *this;
  }

  constexpr auto operator/=(const Self& rhs) -> Self& {
    value /= rhs.value;
    return *this;
  }

  constexpr auto operator%=(const Self& rhs) -> Self& {
    value %= rhs.value;
    return *this;
  }

  constexpr friend auto operator==(self_type lhs, self_type rhs) -> bool {
    return lhs.value == rhs.value;
  }

  constexpr friend auto operator!=(self_type lhs, self_type rhs) -> bool {
    return !(lhs == rhs);
  }

  constexpr friend auto operator<(self_type lhs, self_type rhs) -> bool {
    return lhs.value < rhs.value;
  }

  constexpr friend auto operator>(self_type lhs, self_type rhs) -> bool {
    return rhs < lhs;
  }

  constexpr friend auto operator<=(self_type lhs, self_type rhs) -> bool {
    return !(rhs < lhs);
  }

  constexpr friend auto operator>=(self_type lhs, self_type rhs) -> bool {
    return !(lhs < rhs);
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

struct Duration : public number_wrapper<unsigned long, Duration> {
  constexpr explicit Duration() : number_wrapper<unsigned long, Duration>(0) {}
  constexpr explicit Duration(unsigned long microseconds) : number_wrapper<unsigned long, Duration>(microseconds) {}
  static constexpr auto Seconds(unsigned long amount) -> Duration { return Duration(amount * 1000000); }
  static constexpr auto Minutes(unsigned long amount) -> Duration { return Duration(amount * 60000000); }
  static constexpr auto Milliseconds(unsigned long amount) -> Duration { return Duration(amount * 1000); }
  static constexpr auto Microseconds(unsigned long amount) -> Duration { return Duration(amount); }
  constexpr auto asSeconds() -> float { return static_cast<float>(value) / 1000000.f; }
  constexpr auto asMinutes() -> float { return static_cast<float>(value) / 60000000.f; }
  constexpr auto asMilliseconds() -> float { return static_cast<float>(value) / 1000.f; }
  constexpr auto asMicroseconds() -> float { return static_cast<float>(value); }
};

struct Timestamp : public number_wrapper<unsigned long, Timestamp> {
  constexpr explicit Timestamp() : number_wrapper<unsigned long, Timestamp>(0) {}
  constexpr explicit Timestamp(unsigned long microseconds) : number_wrapper<unsigned long, Timestamp>(microseconds) {}
  static constexpr auto OfMicroseconds(unsigned long amount) -> Timestamp { return Timestamp(amount); }
  constexpr auto asSeconds() -> float { return static_cast<float>(value) / 1000000.f; }
  constexpr auto asMinutes() -> float { return static_cast<float>(value) / 60000000.f; }
  constexpr auto asMilliseconds() -> float { return static_cast<float>(value) / 1000.f; }
  constexpr auto asMicroseconds() -> float { return static_cast<float>(value); }

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

}

#endif //RGBLIB_TYPES_H
