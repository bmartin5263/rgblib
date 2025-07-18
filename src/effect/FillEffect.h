//
// Created by Brandon on 4/14/25.
//

#ifndef RGBLIB_FILLEFFECT_H
#define RGBLIB_FILLEFFECT_H

#include "Color.h"

namespace rgb {

struct FillEffectShaderParameters {
  Timestamp now;
  u16 length;
  u16 position;

  [[nodiscard]] constexpr normal relativePosition() const {
    return static_cast<float>(position) / static_cast<float>(length);
  }
};

using FillEffectShader = std::function<void(Color&, const FillEffectShaderParameters&)>;

class PixelList;
class FillEffect {
  static auto RainbowShader(Color& pixel, const FillEffectShaderParameters& params) -> void {
    pixel = rgb::Color::HslToRgb(params.relativePosition()) * Brightness::Current();
  }

public:
  auto draw(PixelList& chain) -> void;

  FillEffectShader shader{RainbowShader};
private:

};

}


#endif //RGBLIB_FILLEFFECT_H
