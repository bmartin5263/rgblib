//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_OPTIMIZATIONAPPLICATION_H
#define RGBLIB_OPTIMIZATIONAPPLICATION_H

#include "VehicleApplication.h"
#include "FastLEDMatrix.h"

using namespace rgb;

auto grid = FastLEDMatrix<8, 8, D2_RGB, RgbwSupport::ENABLE, 3, 2>();

class OptimizationApplication : public VehicleApplication<> {
protected:
  auto configure(VehicleApplication::Configurer& app) -> void override {
    grid.setBrightness(.5f);
    app.addLEDs(grid);
    app.useHeartbeatLED();
  }

  auto update() -> void override {
  }

  auto draw() -> void override {
    grid.fill(Color::BLUE());
    grid.set(0, 0, Color::PURPLE());
    grid.set(0, 1, Color::ORANGE());
    grid.set(1, 0, Color::GREEN());
    grid.set(1, 1, Color::RED());
  }
};


#endif //RGBLIB_OPTIMIZATIONAPPLICATION_H
