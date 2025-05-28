//
// Created by Brandon on 5/26/25.
//

#ifndef RGBLIB_ITERABLE_H
#define RGBLIB_ITERABLE_H

#include <array>

namespace rgb {

template <typename T>
struct Iterable {

  constexpr Iterable(): mBegin(nullptr), mEnd(nullptr) {}

  constexpr Iterable(T* begin, T* end): mBegin(begin), mEnd(end) {}

  template<size_t N>
  constexpr Iterable(std::array<T, N>& array): mBegin(array.begin()), mEnd(array.end()) {}

  constexpr auto begin() -> T* { return mBegin; };
  constexpr auto end() -> T* { return mEnd; };
  constexpr auto begin() const -> const T* { return mBegin; };
  constexpr auto end() const -> const T* { return mEnd; };

  T* mBegin;
  T* mEnd;
};

}

#endif //RGBLIB_ITERABLE_H
