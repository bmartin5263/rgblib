//
// Created by Brandon on 8/17/25.
//

#ifndef RGBLIB_WIPEEFFECT_H
#define RGBLIB_WIPEEFFECT_H

#include <optional>
#include "Types.h"
#include "PixelList.h"
#include "Iterable.h"
#include "Length.h"
#include "EffectProgression.h"
#include "Effect.h"

namespace rgb {

class WipeEffect : public Effect {
public:
  struct ShaderParameters {
    Timestamp now{};
    Duration duration{};
    uint wipeLength{};
    uint wipeCycle{};
    uint pixelPosition{};
    normal positionRatio{};
    normal brightness{};
  };
  using Shader = std::function<Pixel(Pixel, const ShaderParameters&)>;
  static constexpr auto DefaultShader = [](auto pixel, const ShaderParameters& params){
    if (params.pixelPosition <= params.wipeLength) {
      return Color::Sequential12(params.wipeCycle) * params.brightness;
    }
    if (params.wipeCycle == 0) {
      return Color::OFF();
    }
    else {
      return Color::Sequential12(params.wipeCycle - 1) * params.brightness;
    }
  };

  // Draw the effect onto a pixel buffer
  auto draw(Timestamp now, PixelList& pixels) -> void override;

  // How to color the pixels lit up by this effect
  Shader shader{DefaultShader};

  // Time it takes for the effect to complete a full cycle
  EffectProgression progression{EffectProgression::ConstantSpeed(Duration::Milliseconds(100))};

};


}

#endif //RGBLIB_WIPEEFFECT_H
