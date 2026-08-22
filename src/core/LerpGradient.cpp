//
// Created by Brandon on 8/22/26.
//

#include "LerpGradient.h"

namespace rgb {

auto LerpGradient::sample(normal position) const -> Color {
  return mFrom.sample(position).lerpClamp(mTo.sample(position), mFactor);
}

auto lerp(const Gradient& from, const Gradient& to, normal factor) -> LerpGradient {
  return LerpGradient{from, to, factor};
}

auto LerpColorGradient::sample(normal position) const -> Color {
  return mFrom.sample(position).lerpClamp(mTo, mFactor);
}

auto lerp(const Gradient& from, Color to, normal factor) -> LerpColorGradient {
  return LerpColorGradient{from, to, factor};
}

auto ColorLerpGradient::sample(normal position) const -> Color {
  return mFrom.lerpClamp(mTo.sample(position), mFactor);
}

auto lerp(Color from, const Gradient& to, normal factor) -> ColorLerpGradient {
  return ColorLerpGradient{from, to, factor};
}

}
