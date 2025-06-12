//
// Created by Brandon on 6/8/25.
//

#ifndef RGBLIB_CIRCULARBUFFER_H
#define RGBLIB_CIRCULARBUFFER_H

#include <array>

template <typename TNumeric, size_t TMaxSampleSize>
struct DataSet {

  constexpr auto push(TNumeric number) -> void {
    data[next] = number;
    next = (next + 1) % sampleSize;
    if (next == 0) {
      full = true;
    }
  }

  constexpr auto count() const -> size_t {
    return full ? sampleSize : next;
  }

  constexpr auto average() const -> float {
    auto sz = count();
    if (sz == 0) {
      return 0.0f;
    }
    auto result = TNumeric{};
    for (size_t i = 0; i < sz; ++i) {
      result += data[i];
    }
    return static_cast<float>(result) / sz;
  }

  constexpr auto clear() -> void {
    std::fill(data.begin(), data.end(), TNumeric{});
    full = false;
    next = 0;
  }

  constexpr auto adjustSampleSize(size_t newSampleSize) -> void {
    if (newSampleSize > sampleSize) {
      full = false;
      next = newSampleSize;
    }
  }

  std::array<TNumeric, TMaxSampleSize> data{};
  size_t next{};
  size_t sampleSize{TMaxSampleSize};
  bool full{};
};

#endif //RGBLIB_CIRCULARBUFFER_H
