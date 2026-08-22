//
// Created by Brandon on 8/22/26.
//

#include "GradientView.h"

namespace rgb {

auto GradientView::sample(normal position) const -> Color {
  return mSource.sample(position) * mBrightness;
}

auto GradientView::operator*(normal brightness) const -> GradientView {
  return GradientView{mSource, mBrightness * brightness};
}

auto operator*(const Gradient& gradient, normal brightness) -> GradientView {
  return GradientView{gradient, brightness};
}

}
