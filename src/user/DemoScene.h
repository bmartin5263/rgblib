//
// Created by Brandon on 4/19/25.
//

#ifndef RGBLIB_DEMOSCENE_H
#define RGBLIB_DEMOSCENE_H

#include "Scene.h"
#include "FillEffect.h"
#include "Vehicle.h"

class DemoScene : public rgb::Scene {
public:
  explicit DemoScene(rgb::LEDChain& ring, rgb::LEDChain& stick);
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;

private:
  rgb::LEDChain& ring;
  rgb::LEDChain& stick;
  rgb::FillEffect fillEffect{};

};


#endif //RGBLIB_DEMOSCENE_H
