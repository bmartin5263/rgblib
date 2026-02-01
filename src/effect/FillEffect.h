//
// Created by Brandon on 4/14/25.
//

#ifndef RGBLIB_FILLEFFECT_H
#define RGBLIB_FILLEFFECT_H

#include <functional>
#include "rgb/Color.h"
#include "Brightness.h"
#include "Effect.h"

namespace rgb {

struct FillEffectShaderParameters {
  Timestamp now{};
  uint length{};
  uint position{};

  [[nodiscard]] constexpr normal relativePosition() const {
    return static_cast<float>(position) / static_cast<float>(length);
  }
};
using FillEffectShader = std::function<Color(Color, const FillEffectShaderParameters&)>;

class FillEffect : public Effect {
  static auto RainbowShader(Color pixel, const FillEffectShaderParameters& params) -> Color {
    return rgb::Color::HslToRgb(params.relativePosition()) * Brightness::GetBrightness(1.0f);
  }

public:
  auto draw(Timestamp now, PixelList& pixels) -> void override;
  FillEffectShader shader{RainbowShader};
private:

};

}


#endif //RGBLIB_FILLEFFECT_H
