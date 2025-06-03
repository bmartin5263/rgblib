//
// Created by Brandon on 4/15/25.
//

#ifndef RGBLIB_TRAILINGEFFECT_H
#define RGBLIB_TRAILINGEFFECT_H

#include <functional>
#include <limits>
#include "Types.h"
#include "Color.h"

namespace rgb {

struct TrailingEffectShaderParameters {
  rgb::Timestamp now;
  rgb::Duration speed;
  rgb::u16 trailLength;
  rgb::u16 absolutePosition;
  rgb::u16 relativePosition;
  float positionRatio;
};

using TrailingEffectShader = std::function<void(Color&, const TrailingEffectShaderParameters&)>;

class PixelList;
class TrailingEffect {
public:
  constexpr static auto DefaultShader(Color& color, const TrailingEffectShaderParameters&) -> void {
    color = Color::CYAN(.01);
  }

  auto init() -> void;
  auto update() -> void;
  auto draw(PixelList& chain) -> void;

  TrailingEffectShader shader{DefaultShader};
  Duration speed{Duration::Milliseconds(500)};
  normal trailRatio{.5f};
  int offset{0};
  int endBuffer{0};
  int startBuffer{0};
  uint cycles{std::numeric_limits<uint>::max()};
private:
  int pixel{0};
  Timestamp nextMoveTime{0};

  auto move() -> void;
};

}


#endif //RGBLIB_TRAILINGEFFECT_H
