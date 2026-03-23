//
// Created by Brandon on 4/14/25.
//

#ifndef RGBLIB_FILLEFFECT_H
#define RGBLIB_FILLEFFECT_H

#include <functional>
#include "core/Color.h"
#include "Brightness.h"
#include "Effect.h"

namespace rgb {

struct FillEffectShaderParameters {
  Timestamp now{};
  uint length{};
  uint position{};
  float brightness{};

  [[nodiscard]] constexpr normal relativePosition() const {
    return static_cast<float>(position) / static_cast<float>(length);
  }
};
using FillEffectShader = std::function<Color(Color, const FillEffectShaderParameters&)>;

class FillEffect : public Effect {
  static auto RainbowShader(Color pixel, const FillEffectShaderParameters& params) -> Color {
    return rgb::Color::HslToRgb(params.relativePosition()) * params.brightness;
  }

public:
  auto draw(Timestamp now, PixelList& pixels) -> void override;
  FillEffectShader shader{RainbowShader};

  // How bright the effect is under different preset brightness settings
  BrightnessLevels brightness{};

private:

};

}


#endif //RGBLIB_FILLEFFECT_H
