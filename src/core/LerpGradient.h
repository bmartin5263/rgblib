//
// Created by Brandon on 8/22/26.
//

#ifndef RGBLIB_LERPGRADIENT_H
#define RGBLIB_LERPGRADIENT_H

#include "Gradient.h"
#include "RgbColor.h"
#include "Types.h"

namespace rgb {

class LerpGradient : public Gradient {
public:
  LerpGradient(const Gradient& from, const Gradient& to, normal factor) : mFrom(from), mTo(to), mFactor(factor) {}

  [[nodiscard]] auto sample(normal position) const -> Color override;

private:
  const Gradient& mFrom;
  const Gradient& mTo;
  normal mFactor;
};

auto lerp(const Gradient& from, const Gradient& to, normal factor) -> LerpGradient;

class LerpColorGradient : public Gradient {
public:
  LerpColorGradient(const Gradient& from, Color to, normal factor) : mFrom(from), mTo(to), mFactor(factor) {}

  [[nodiscard]] auto sample(normal position) const -> Color override;

private:
  const Gradient& mFrom;
  Color mTo;
  normal mFactor;
};

auto lerp(const Gradient& from, Color to, normal factor) -> LerpColorGradient;

class ColorLerpGradient : public Gradient {
public:
  ColorLerpGradient(Color from, const Gradient& to, normal factor) : mFrom(from), mTo(to), mFactor(factor) {}

  [[nodiscard]] auto sample(normal position) const -> Color override;

private:
  Color mFrom;
  const Gradient& mTo;
  normal mFactor;
};

auto lerp(Color from, const Gradient& to, normal factor) -> ColorLerpGradient;

}

#endif //RGBLIB_LERPGRADIENT_H
