//
// Created by Brandon on 2/2/26.
//

#ifndef RGBLIB_CHASINGEFFECTSPEEDONLY_H
#define RGBLIB_CHASINGEFFECTSPEEDONLY_H

#include <optional>
#include "Types.h"
#include "PixelList.h"
#include "Iterable.h"
#include "Length.h"
#include "EffectProgression.h"
#include "Effect.h"
#include "Brightness.h"

namespace rgb {

// Only permits speed-based progression
class ChasingEffectSpeedOnly : public Effect {
public:
  struct ShaderParameters {
    Timestamp now{};
    Duration delay{};
    uint trailLength{};
    uint pixelPosition{};
    uint trailPosition{};
    float positionRatio{};
  };
  using Shader = std::function<Color(Color, const ShaderParameters&)>;
  static constexpr auto DefaultShader = [](auto color, auto& params){
    return Color::MAGENTA() * .3f;
  };

  // Reset the state of the effect
  auto reset(Timestamp now) -> void override;

  // Update the effect (call every frame)
  auto update(Timestamp now) -> void override;

  // Step the effect by a single frame
  auto step() -> void;

  // Draw the effect onto a pixel buffer
  auto draw(Timestamp now, PixelList& pixels) -> void override;

  // How to color the pixels lit up by this effect
  Shader shader{DefaultShader};

  // Time between position updates
  Duration delay{Duration::Milliseconds(100)};

private: // TODO - see if this organization affected the memory size
  // When do we move the effect next
  rgb::Timestamp nextMoveTime{0};

  // Where is the head of the effect
  u64 effectPosition{0};

public:
  // How much the effect should be shifted
  i64 shift{0};

  // Length of the chase trail, in absolute units or relative to the length of the pixel buffer
  Length trailLength{.2f};

  // Does the trail have to first enter from "off-screen"
  bool buildup{false};

};


}

#endif //RGBLIB_CHASINGEFFECTSPEEDONLY_H
