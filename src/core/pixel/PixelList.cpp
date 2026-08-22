//
// Created by Brandon on 1/5/25.
//

#include "PixelList.h"

#include "Assertions.h"
#include "Gradient.h"
#include "RgbColor.h"

namespace rgb {

auto PixelList::fill(const Color& color) -> void {
  fill(color, 0, length());
}

auto PixelList::fill(const Color& color, uint range) -> void {
  fill(color, 0, range);
}

auto PixelList::fill(const Color& color, uint start, uint endExclusive) -> void {
  endExclusive = Min(length(), endExclusive);
  for (auto i = start; i < endExclusive; ++i) {
    set(i, color);
  }
}

auto PixelList::fillRatio(const Color& color, normal fillPercent) -> void {
  if (fillPercent > 1.0f) {
    fillPercent = 1.0f;
  }
  auto range = static_cast<uint>(size() * fillPercent);
  range = Min(range, size());
  fill(color, 0, range);
}

auto PixelList::fillRatio(const Gradient& gradient, normal fillPercent, normal offset, normal scale) -> void {
  if (fillPercent > 1.0f) {
    fillPercent = 1.0f;
  }
  auto range = static_cast<uint>(size() * fillPercent);
  range = Min(range, size());
  fill(gradient, 0, range, offset, scale);
}

auto PixelList::fillReverse(const Color& color, uint range) -> void {
  fill(color, size() - range, size());
}

auto PixelList::fillReverse(const Gradient& gradient, uint range, normal offset, normal scale) -> void {
  fill(gradient, size() - range, size(), offset, scale);
}

auto PixelList::fillRatioReverse(const Color& color, normal fillPercent) -> void {
  if (fillPercent > 1.0f) {
    fillPercent = 1.0f;
  }
  auto range = static_cast<uint>(size() * fillPercent);
  range = std::min(range, size());
  fill(color, size() - range, size());
}

auto PixelList::fillRatioReverse(const Gradient& gradient, normal fillPercent, normal offset, normal scale) -> void {
  if (fillPercent > 1.0f) {
    fillPercent = 1.0f;
  }
  auto range = static_cast<uint>(size() * fillPercent);
  range = Min(range, size());
  fill(gradient, size() - range, size(), offset, scale);
}

auto PixelList::fill(const Gradient& gradient, normal offset, normal scale) -> void {
  fill(gradient, 0, length(), offset, scale);
}

auto PixelList::fill(const Gradient& gradient, uint range, normal offset, normal scale) -> void {
  fill(gradient, 0, range, offset, scale);
}

auto PixelList::fill(const Gradient& gradient, uint start, uint endExclusive, normal offset, normal scale) -> void {
  ASSERT(start < endExclusive, "start must be less than endExclusive");
  ASSERT(endExclusive <= length(), "endExclusive out of range");
  auto lastIndex = static_cast<float>(endExclusive - start - 1);
  for (uint i = start; i < endExclusive; ++i) {
    auto percentBetween = PercentBetween(static_cast<float>(i - start), 0.0f, lastIndex);
    auto dividedByScale = percentBetween / scale;
    auto position = WrapUnit(dividedByScale + offset);
    set(i, gradient.sample(position));
  }
}

auto PixelList::clear() -> void {
  fill(Color::OFF());
}

auto PixelList::begin() -> PixelIterator {
  return {this, 0};
}

auto PixelList::begin() const -> ConstPixelIterator {
  return {const_cast<PixelList*>(this), 0};
}

auto PixelList::end() -> PixelIterator {
  return {this, length()};
}

auto PixelList::end() const -> ConstPixelIterator {
  return {const_cast<PixelList*>(this), length()};
}

}