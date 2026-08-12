//
// Created by Brandon on 8/11/26.
//

#ifndef RGBLIB_GRADIENTSOURCE_H
#define RGBLIB_GRADIENTSOURCE_H

#include "RgbColor.h"
#include "Types.h"

namespace rgb {

class Gradient {
public:
  Gradient() = default;
  virtual ~Gradient() = default;
  Gradient(const Gradient& rhs) = default;
  Gradient(Gradient&& rhs) noexcept = default;
  Gradient& operator=(const Gradient& rhs) = default;
  Gradient& operator=(Gradient&& rhs) noexcept = default;

  [[nodiscard]] virtual auto sample(normal position) const -> Color = 0;
};

}

#endif //RGBLIB_GRADIENTSOURCE_H
