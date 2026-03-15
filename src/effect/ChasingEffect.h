//
// Created by Brandon on 8/17/25.
//

#ifndef RGBLIB_CHASINGEFFECT_H
#define RGBLIB_CHASINGEFFECT_H

#include <optional>
#include "Types.h"
#include "PixelList.h"
#include "Iterable.h"
#include "Length.h"
#include "EffectProgression.h"
#include "Effect.h"
#include "Brightness.h"

namespace rgb {

/*
 * Length Modes:
 *   Absolute  - Trail length is defined in absolute units
 *   Relative* - Trail length is defined as a ratio of the length of the LED strip
 *
 * Progress Modes:
 *   StepBased   - The trail moves at the same speed no matter the length of the LED strip
 *   ChainBased* - The trail moves at a speed that depends on how long the effect should take
 */
class ChasingEffect : public Effect {
public:
  struct ShaderParameters {
    Timestamp now{};
    Duration duration{};
    uint trailLength{};
    uint pixelPosition{};
    uint trailPosition{};
    uint cycle{};
    float positionRatio{};
    float brightness{};
  };
  using Shader = std::function<Color(Color, const ShaderParameters&)>;
  static constexpr auto DefaultShader = [](auto color, auto& params){
    return Color::MAGENTA() * .3f;
  };

  // Draw the effect onto a pixel buffer
  auto draw(Timestamp now, PixelList& pixels) -> void override;

  // How to color the pixels lit up by this effect
  Shader shader{DefaultShader};

  // Time it takes for the effect to complete a full cycle
  EffectProgression progression{DEFAULT_PROGRESSION};

  // How much the effect should be shifted
  i64 shift{0};

  BrightnessLevels brightness{};

  // Length of the chase trail, in absolute units or relative to the length of the pixel buffer
  Length trailLength{.2f};

  // Does the trail enter from "off-screen"?
  bool buildup{true};

};


}

#endif //RGBLIB_CHASINGEFFECT_H
