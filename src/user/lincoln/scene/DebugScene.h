//
// Created by Brandon on 4/19/25.
//

#ifndef RGBLIB_DEBUGSCENE_H
#define RGBLIB_DEBUGSCENE_H

#include "Scene.h"
#include "FillEffect.h"
#include "Vehicle.h"

class DebugScene : public rgb::Scene {
public:
  explicit DebugScene(rgb::LEDChain& ring, rgb::Vehicle& vehicle);
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;

private:
  rgb::LEDChain& ring;
  rgb::Vehicle& vehicle;
  rgb::FillEffect fillEffect{};

};


#endif //RGBLIB_DEBUGSCENE_H
