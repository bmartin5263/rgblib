//
// Created by Brandon on 4/19/25.
//

#ifndef RGBLIB_DEMOSCENE_H
#define RGBLIB_DEMOSCENE_H

#include "Scene.h"
#include "FillEffect.h"
#include "Vehicle.h"
#include "IRReceiver.h"

class DemoScene : public rgb::Scene {
public:
  explicit DemoScene(rgb::PixelList& ring, rgb::IRReceiver& irReceiver);
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;

public:
  rgb::PixelList& ring;
  rgb::IRReceiver& irReceiver;
  rgb::FillEffect fillEffect{};
  rgb::Color color{rgb::Color::BLUE(1.0f)};
};


#endif //RGBLIB_DEMOSCENE_H
