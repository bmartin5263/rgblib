//
// Created by Brandon on 4/6/26.
//

#ifndef RGBLIB_CAROUSEL_H
#define RGBLIB_CAROUSEL_H

#include "Types.h"
#include <array>

namespace rgb {

/**
 * A read-only array combined with an index. You can only get the value at index.
 */
template<typename T, size_t N>
class Carousel {
public:
  explicit constexpr Carousel(std::array<T, N> items) : mItems(std::move(items)) {}

  constexpr auto get() const -> const T& {
    return mItems[mIndex];
  }

  constexpr auto next() -> const T& {
    mIndex = (mIndex + 1) % N;
    return get();
  }

  constexpr auto prev() -> const T& {
    mIndex = (mIndex + N - 1) % N;
    return get();
  }

  constexpr auto set(size_t position) -> const T& {
    mIndex = position % N;
    return get();
  }

  constexpr auto index() const -> size_t {
    return mIndex;
  }

  constexpr auto size() const -> size_t {
    return N;
  }

private:
  std::array<T, N> mItems;
  size_t mIndex{0};
};

}

#endif //RGBLIB_CAROUSEL_H
