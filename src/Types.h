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

using milliseconds = unsigned long;
using microseconds = unsigned long;
using frames = unsigned long;
using pin_num = i8;
using cstring = const char*;

//template<typename V, class Self>
//struct number_wrapper {
//  V value;
//
//  constexpr explicit number_wrapper(V value) : value(value) {}
//
//  using mytype = number_wrapper<V, Self>;
//
//  constexpr auto operator=(V rhs) -> mytype& {
//    value = rhs;
//    return *this;
//  }
//
//  constexpr auto operator+(const Self& rhs) const -> Self {
//    return Self { value + rhs.value };
//  }
//
//  constexpr auto operator-(const Self& rhs) const -> Self {
//    return Self { value - rhs.value };
//  }
//
//  constexpr auto operator+(V rhs) const -> Self {
//    return Self { value + rhs } ;
//  }
//
//  constexpr auto operator-(V rhs) const -> Self {
//    return Self { value - rhs };
//  }
//
//  constexpr auto operator+=(Self rhs) -> Self& {
//    value += rhs.value;
//    return *this;
//  }
//
//  constexpr auto operator-=(Self rhs) -> Self& {
//    value -= rhs.value;
//    return *this;
//  }
//
//  constexpr auto operator*=(Self rhs) -> Self& {
//    value *= rhs.value;
//    return *this;
//  }
//
//  constexpr auto operator/=(Self rhs) -> Self& {
//    value /= rhs.value;
//    return *this;
//  }
//
//  constexpr auto operator+=(V rhs) -> Self& {
//    value += rhs;
//    return *this;
//  }
//
//  constexpr auto operator-=(V rhs) -> Self& {
//    value -= rhs;
//    return *this;
//  }
//
//  constexpr auto operator*=(V rhs) -> Self& {
//    value *= rhs;
//    return *this;
//  }
//
//  constexpr auto operator/=(V rhs) -> Self& {
//    value /= rhs;
//    return *this;
//  }
//
//  constexpr friend auto operator==(mytype lhs, mytype rhs) -> bool {
//    return lhs.value == rhs.value;
//  }
//
//  constexpr friend auto operator!=(mytype lhs, mytype rhs) -> bool {
//    return !(lhs == rhs);
//  }
//
//  constexpr friend auto operator<(mytype lhs, mytype rhs) -> bool {
//    return lhs.value < rhs.value;
//  }
//
//  constexpr friend auto operator>(mytype lhs, mytype rhs) -> bool {
//    return rhs < lhs;
//  }
//
//  constexpr friend auto operator<=(mytype lhs, mytype rhs) -> bool {
//    return !(rhs < lhs);
//  }
//
//  constexpr friend auto operator>=(mytype lhs, mytype rhs) -> bool {
//    return !(lhs < rhs);
//  }
//
//  constexpr friend auto operator==(mytype lhs, V rhs) -> bool {
//    return lhs.value == rhs;
//  }
//
//  constexpr friend auto operator!=(mytype lhs, V rhs) -> bool {
//    return !(lhs == rhs);
//  }
//
//  constexpr friend auto operator<(mytype lhs, V rhs) -> bool {
//    return lhs.value < rhs;
//  }
//
//  constexpr friend auto operator>(mytype lhs, V rhs) -> bool {
//    return rhs < lhs;
//  }
//
//  constexpr friend auto operator<=(mytype lhs, V rhs) -> bool {
//    return !(rhs < lhs);
//  }
//
//  constexpr friend auto operator>=(mytype lhs, V rhs) -> bool {
//    return !(lhs < rhs);
//  }
//
//  constexpr auto operator++() -> Self& {
//    ++value;
//    return static_cast<Self&>(*this);
//  }
//
//  constexpr auto operator++(int) -> Self {
//    Self tmp(*this);
//    operator++();
//    return tmp;
//  }
//};
//
//struct seconds : public number_wrapper<long, seconds> {
//  constexpr explicit seconds(long value = 0) : number_wrapper<long, seconds>(value) {}
//};
//
//struct milliseconds : public number_wrapper<long, milliseconds> {
//  constexpr explicit milliseconds(long value = 0) : number_wrapper<long, milliseconds>(value) {}
//};
//
//struct microseconds : public number_wrapper<long, microseconds> {
//  constexpr explicit microseconds(long value = 0) : number_wrapper<long, microseconds>(value) {}
//};
//
//struct frames : public number_wrapper<long, frames> {
//  constexpr explicit frames(long value = 0) : number_wrapper<long, frames>(value) {}
//};
//
//struct seconds_u : public number_wrapper<unsigned long, seconds_u> {
//  constexpr explicit seconds_u(unsigned long value = 0) : number_wrapper<unsigned long, seconds_u>(value) {}
//};
//
//struct milliseconds_u : public number_wrapper<unsigned long, milliseconds_u> {
//  constexpr explicit milliseconds_u(unsigned long value = 0) : number_wrapper<unsigned long, milliseconds_u>(value) {}
//};
//
//struct microseconds_u : public number_wrapper<unsigned long, microseconds_u> {
//  constexpr explicit microseconds_u(unsigned long value = 0) : number_wrapper<unsigned long, microseconds_u>(value) {}
//};
//
//struct frames_u : public number_wrapper<unsigned long, frames_u> {
//  constexpr explicit frames_u(unsigned long value = 0) : number_wrapper<unsigned long, frames_u>(value) {}
//};

}

#endif //RGBLIB_TYPES_H
