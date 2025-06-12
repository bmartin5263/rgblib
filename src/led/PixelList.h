//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_PIXELLIST_H
#define RGBLIB_PIXELLIST_H

#include "Types.h"
#include "Pixel.h"

namespace rgb {

struct FillChain {
  FillChain(Pixel* head, u16 size);

  auto fill(const Pixel& color) -> FillChain;
  auto fill(const Pixel& color, u16 range) -> FillChain;
  auto fill(const Pixel& color, u16 start, u16 range) -> FillChain;

  Pixel* mHead{};
  u16 mSize{};
};

struct Point;
class PixelSlice;
class PixelList {
public:
  [[nodiscard]] virtual auto getHead() -> Pixel* = 0;
  [[nodiscard]] virtual auto getHead() const -> const Pixel* = 0;
  [[nodiscard]] virtual auto getSize() const -> u16 = 0;

  [[nodiscard]] auto get(u16 pixel) -> Pixel*;
  [[nodiscard]] auto operator[](u16 pixel) -> Pixel&;

  auto fill(const Color& color) -> FillChain;
  auto fill(const Color& color, u16 range) -> FillChain;
  auto fill(const Color& color, u16 start, u16 range) -> FillChain;
  auto clear() -> void;
  auto set(u16 pixel, const Color& color) -> void;

  auto slice(u16 length) -> PixelSlice;
  auto slice(u16 start, u16 length) -> PixelSlice;

  [[nodiscard]] auto begin() -> Pixel*;
  [[nodiscard]] auto begin() const -> const Pixel*;
  [[nodiscard]] auto end() -> Pixel*;
  [[nodiscard]] auto end() const -> const Pixel*;

  PixelList() = default;
  PixelList(const PixelList& rhs) = default;
  PixelList(PixelList&& rhs) noexcept = default;
  PixelList& operator=(const PixelList& rhs) = default;
  PixelList& operator=(PixelList&& rhs) noexcept = default;
  virtual ~PixelList() = default;
};

class NullPixelList : public PixelList {
public:
  auto getHead() -> Pixel* override;
  auto getHead() const -> const Pixel* override;
  auto getSize() const -> u16 override;


  static auto Instance() -> NullPixelList& {
    static NullPixelList instance;
    return instance;
  }
};

using PixelStrip = PixelList;
using PixelRing = PixelList;

}

#endif //RGBLIB_PIXELLIST_H
