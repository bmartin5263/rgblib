//
// Created by Brandon on 5/26/25.
//

#ifndef RGBLIB_DRAWABLE_H
#define RGBLIB_DRAWABLE_H

namespace rgb {

class Drawable {
public:
  Drawable() = default;
  Drawable(const Drawable& rhs) = default;
  Drawable(Drawable&& rhs) noexcept = default;
  Drawable& operator=(const Drawable& rhs) = default;
  Drawable& operator=(Drawable&& rhs) noexcept = default;
  virtual ~Drawable() = default;

  virtual auto reset() -> void = 0;
  virtual auto display() -> void = 0;
};


}
#endif //RGBLIB_DRAWABLE_H
