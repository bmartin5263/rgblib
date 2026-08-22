//
// Created by Brandon on 8/22/26.
//

#ifndef RGBLIB_GRADIENTVIEW_H
#define RGBLIB_GRADIENTVIEW_H

#include "Gradient.h"
#include "RgbColor.h"
#include "Types.h"

namespace rgb {

class GradientView : public Gradient {
public:
  GradientView(const Gradient& source, Color tint) : mSource(source), mTint(tint) {}

  [[nodiscard]] auto sample(normal position) const -> Color override;

  auto operator*(const Color& tint) const -> GradientView;
  auto operator*(normal brightness) const -> GradientView;

private:
  const Gradient& mSource;
  Color mTint;
};

auto operator*(const Gradient& gradient, const Color& tint) -> GradientView;
auto operator*(const Gradient& gradient, normal brightness) -> GradientView;

}

#endif //RGBLIB_GRADIENTVIEW_H
