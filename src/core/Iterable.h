//
// Created by Brandon on 5/26/25.
//

#ifndef RGBLIB_ITERABLE_H
#define RGBLIB_ITERABLE_H

#include <array>
#include "Func.h"

namespace rgb {

template <typename T>
struct Iterable {

  constexpr Iterable(): mBegin(nullptr), mSize(0) {}

  template<size_t N>
  constexpr Iterable(std::array<T, N>& array): mBegin(array.begin()), mSize(array.size()) {}

  constexpr auto operator[](size_t index) -> T& { return *(begin() + index); }

  constexpr auto begin() -> T* { return mBegin; };
  constexpr auto end() -> T* { return mBegin + mSize; };
  constexpr auto begin() const -> const T* { return mBegin; };
  constexpr auto end() const -> const T* { return mBegin + mSize; };
  constexpr auto size() const -> size_t { return mSize; };

  constexpr auto forEach(Consumer<T> function) {
    for (auto& item : *this) {
      function(item);
    }
  }

  T* mBegin;
  size_t mSize;
};

}

#endif //RGBLIB_ITERABLE_H
