//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_NATIVERENDERABLE_H
#define RGBLIB_NATIVERENDERABLE_H

#include "Types.h"
#include "Pixel.h"

namespace rgb {

class NativeRenderable {
public:
  NativeRenderable() = default;
  virtual ~NativeRenderable() = default;

  virtual auto pixelCount() const -> u16 = 0;
  virtual auto columns() const -> uint = 0;
  // Multiplier applied to NativeDisplay's base pixel size/pitch, so visually smaller devices
  // (e.g. fiber strands) can render smaller than a full LED strip/matrix pixel.
  virtual auto pixelScale() const -> normal = 0;
  virtual auto renderedPixel(u16 index) const -> Pixel = 0;

protected:
  NativeRenderable(const NativeRenderable& rhs) = default;
  NativeRenderable(NativeRenderable&& rhs) noexcept = default;
  NativeRenderable& operator=(const NativeRenderable& rhs) = default;
  NativeRenderable& operator=(NativeRenderable&& rhs) noexcept = default;
};

}

#endif //RGBLIB_NATIVERENDERABLE_H
