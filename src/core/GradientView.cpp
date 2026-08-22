//
// Created by Brandon on 8/22/26.
//

#include "GradientView.h"

namespace rgb {

auto GradientView::sample(normal position) const -> Color {
  return mSource.sample(position) * mTint;
}

auto GradientView::operator*(const Color& tint) const -> GradientView {
  return GradientView{mSource, mTint * tint};
}

auto GradientView::operator*(normal brightness) const -> GradientView {
  return GradientView{mSource, mTint * Color{brightness, brightness, brightness, brightness}};
}

auto operator*(const Gradient& gradient, const Color& tint) -> GradientView {
  return GradientView{gradient, tint};
}

auto operator*(const Gradient& gradient, normal brightness) -> GradientView {
  return GradientView{gradient, Color{brightness, brightness, brightness, brightness}};
}

}
