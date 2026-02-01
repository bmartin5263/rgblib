//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_PIXELLIST_H
#define RGBLIB_PIXELLIST_H

#include "Types.h"
#include "Pixel.h"

namespace rgb {

struct Point;
class PixelList;

template<typename PixelType>
class PixelIteratorBase;

using PixelIterator = PixelIteratorBase<Pixel>;
using ConstPixelIterator = PixelIteratorBase<const Pixel>;

class PixelList {
public:
  [[nodiscard]] virtual auto length() const -> uint = 0;
  [[nodiscard]] virtual auto get(uint pixel) const -> Pixel = 0;
  virtual auto set(uint pixel, const Color& color) -> void = 0;

  auto fill(const Color& color) -> void;
  auto fill(const Color& color, uint range) -> void;
  auto fill(const Color& color, uint start, uint endExclusive) -> void;
  auto clear() -> void;
  auto size() const -> uint { return length(); };

  auto begin() -> PixelIterator;
  auto begin() const -> ConstPixelIterator;
  auto end() -> PixelIterator;
  auto end() const -> ConstPixelIterator;

  PixelList() = default;
  PixelList(const PixelList& rhs) = default;
  PixelList(PixelList&& rhs) noexcept = default;
  PixelList& operator=(const PixelList& rhs) = default;
  PixelList& operator=(PixelList&& rhs) noexcept = default;
  virtual ~PixelList() = default;
};

class PixelProxy {
  PixelList* list;
  uint index;
public:
  PixelProxy(PixelList* list, uint index) : list(list), index(index) {}

  operator Pixel() const { return list->get(index); } // NOLINT(*-explicit-constructor)

  auto operator=(const Color& color) -> PixelProxy& {
    list->set(index, color);
    return *this;
  }
};

class PixelPointerProxy {
  Pixel pixel;
public:
  explicit PixelPointerProxy(Pixel p) : pixel(p) {}
  auto operator->() -> Pixel* { return &pixel; }
};


template<typename PixelType>
class PixelIteratorBase {
public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = PixelType;
  using pointer = PixelType*;
  using reference = PixelType&;

  PixelIteratorBase(PixelList* list, uint index) : mList(list), mIndex(index) {}

  auto operator*() const -> PixelProxy { return PixelProxy{mList, mIndex}; }
  auto operator->() const -> PixelPointerProxy { return PixelPointerProxy{mList->get(mIndex)}; }

  auto operator++() -> PixelIteratorBase& { ++mIndex; return *this; }
  auto operator++(int) -> PixelIteratorBase { auto tmp = *this; ++mIndex; return tmp; }

  auto operator==(const PixelIteratorBase& other) const -> bool {
    return mIndex == other.mIndex;
  }
  auto operator!=(const PixelIteratorBase& other) const -> bool {
    return mIndex != other.mIndex;
  }

private:
  PixelList* mList;
  uint mIndex;
};

using PixelStrip = PixelList;
using PixelRing = PixelList;

}

#endif //RGBLIB_PIXELLIST_H
