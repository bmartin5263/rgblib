//
// Created by Brandon on 3/17/25.
//

#ifndef RGBLIB_TRAILINGSCENE_H
#define RGBLIB_TRAILINGSCENE_H

#include "Types.h"
#include "Scene.h"
#include "sensor/Vehicle.h"
#include "led/LEDChain.h"

class TrailingScene : public rgb::Scene {
public:
  rgb::Color color{rgb::Color::RED(rgb::ByteToFloat(4))};
  uint moveRate{10};

  explicit TrailingScene(rgb::LEDChain& leds);

  auto update() -> void override;
  auto draw() -> void override;

private:
  rgb::LEDChain& leds;
  uint pixel{0};
  uint moveTime{0};

  auto move() -> void;
};

#endif //RGBLIB_TRAILINGSCENE_H
