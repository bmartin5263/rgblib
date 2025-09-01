//
// Created by Brandon on 8/17/25.
//

#ifndef RGBLIB_CHASINGEFFECT_H
#define RGBLIB_CHASINGEFFECT_H

#include "Types.h"
#include "PixelList.h"
#include "Iterable.h"
#include "Length.h"

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
class ChasingEffect {
public:
  struct ShaderParameters {
    Timestamp now{};
    Duration speed{};
    u16 trailLength{};
    u16 absolutePosition{};
    u16 relativePosition{};
    float positionRatio{};
  };
  using Shader = std::function<void(Color&, const ShaderParameters&)>;
  static constexpr auto DefaultShader = [](auto& color, auto& params){
    color = Color::CYAN(.03f);
  };

  // Reset the state of the effect
  auto reset() -> void;

  // Update the effect (call every frame)
  auto update() -> void;

  // Step the effect by a single frame
  auto step() -> void;

  // Draw the effect onto a pixel buffer
  auto draw(PixelList& pixels) -> void;

  // Draw the effect onto many pixel buffers (should be more efficient than calling draw() many times)
  auto draw(Iterable<PixelList*> pixelLists) -> void;

  // How to color the pixels lit up by this effect
  Shader shader{DefaultShader};

  // Time between position updates
  Duration delay{Duration::Milliseconds(500)}; // Time between position updates

  // Time it takes for the effect to complete a full cycle
  Duration duration{Duration::Seconds(1)}; // Time it takes for the effect to complete a full cycle

private: // TODO - see if this organization affected the memory size
  // When do we move the effect next
  rgb::Timestamp nextMoveTime{0};

  // Where is the head of the effect
  u64 position{0};

public:
  // How much the effect should be shifted
  i64 shift{0};

  // Length of the chase trail, in absolute units or relative to the length of the pixel buffer
  Length trailLength{.5f};

};


}

#endif //RGBLIB_CHASINGEFFECT_H
