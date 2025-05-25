//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_INTROSCENE_H
#define RGBLIB_INTROSCENE_H

#include "Scene.h"
#include "LEDCircuit.h"
#include "FillEffect.h"
#include "TrailingEffect.h"

class IntroScene : public rgb::Scene {
public:
  explicit IntroScene(rgb::LEDRing& ring);
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;
  auto cleanup() -> void override;

  rgb::LEDRing& ring;
  rgb::FillEffect fillEffect{};
  rgb::TrailingEffect trailingEffect{};
};


#endif //RGBLIB_INTROSCENE_H
