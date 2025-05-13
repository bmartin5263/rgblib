//
// Created by Brandon on 3/17/25.
//

#ifndef RGBLIB_TRAILINGSCENE_H
#define RGBLIB_TRAILINGSCENE_H

#include <optional>
#include "Types.h"
#include "Scene.h"
#include "Vehicle.h"
#include "LEDChain.h"

struct TrailingSceneColorGeneratorParameters {
  rgb::Timestamp now;
  rgb::Duration speed;
  rgb::u16 length;
  rgb::u16 absolutePosition;
  rgb::u16 relativePosition;
};

using TrailingSceneColorGenerator = std::function<rgb::Color(const TrailingSceneColorGeneratorParameters&)>;
constexpr auto defaultGenerator(const TrailingSceneColorGeneratorParameters&) -> rgb::Color {
  return rgb::Color::CYAN(.01);
}

struct TrailingSceneParameters {
  rgb::LEDChain* leds{nullptr};
  TrailingSceneColorGenerator colorGenerator{defaultGenerator};
  rgb::Color color{rgb::Color::RED(rgb::ByteToFloat(4))};
  rgb::Duration speed{rgb::Duration::Seconds(1)};
  int shift{0};
  rgb::u16 length{1};
  int endBuffer{0};
  bool continuous{false};

  auto LEDs() -> rgb::LEDChain& {
    return *leds;
  }
};

class TrailingScene : public rgb::Scene {
public:
  explicit TrailingScene(TrailingSceneParameters params);

  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;

  TrailingSceneParameters params;
private:
  int pixel{0};
  rgb::Timestamp nextMoveTime{0};

  auto move() -> void;
};

#endif //RGBLIB_TRAILINGSCENE_H
