//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_OPTIMIZATIONAPPLICATION_H
#define RGBLIB_OPTIMIZATIONAPPLICATION_H

#include "UserApplication.h"
#include "FastLEDMatrix.h"
#include "WipeEffect.h"

using namespace rgb;

auto grid = FastLEDMatrix<8, 8, D2_RGB, RgbwSupport::ENABLE, 3, 2>();
auto wipeEffect = WipeEffect{};

class OptimizationApplication : public UserApplication<> {
protected:
  auto configure(UserApplication::Configurer& app) -> void override {
    grid.setBrightness(.2f);
    app.addLEDs(grid);
    app.useHeartbeatLED();

    wipeEffect.shader = [](auto color, auto& params){
      if (params.pixelPosition <= params.wipeLength) {
        return Color::Sequential12(params.wipeCycle);
      }
      if (params.wipeCycle == 0) {
        return Color::OFF();
      }
      else {
        return Color::Sequential12(params.wipeCycle - 1);
      }
    };
    wipeEffect.progression = EffectProgression::ConstantTime(Duration::Seconds(5));
    Effects::Start(wipeEffect, grid).detach();
  }

  auto update() -> void override {
  }

  auto draw() -> void override {
  }

  auto postDraw() -> void override {
    grid.set(10, 0, Color::BLUE());
    grid.set(0, 10, Color::RED());
    grid.set(10, 10, Color::GREEN());
  }
};


#endif //RGBLIB_OPTIMIZATIONAPPLICATION_H
