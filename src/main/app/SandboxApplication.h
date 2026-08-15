//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_SANDBOXAPPLICATION_H
#define RGBLIB_SANDBOXAPPLICATION_H

#include "UserApplication.h"
#include "FastLEDMatrix.h"
#include "WipeEffect.h"
#include "Every.h"
#include "RgbIIC.h"
#include "RTC.h"

using namespace rgb;

inline auto grid = FastLEDMatrix<8, 8, D2_RGB, RgbwSupport::ENABLE>();

class SandboxApplication : public UserApplication<> {
protected:
  auto configure(Configurer& app) -> void override {
    grid.setBrightness(.2f);
    app.addLEDs(grid);
  }

  auto update() -> void override {
    static auto lastUpdate = Timestamp{};
    if (every(Duration::Seconds(1), lastUpdate)) {
      INFO("update");
    }
  }

  auto draw() -> void override {
  }

  auto postDraw() -> void override {
    grid.fill(Color::BLUE());
  }
};


#endif //RGBLIB_SANDBOXAPPLICATION_H
