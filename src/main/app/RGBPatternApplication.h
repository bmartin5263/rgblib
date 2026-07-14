//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_RGBPATTERNAPPLICATION_H
#define RGBLIB_RGBPATTERNAPPLICATION_H

#include "UserApplication.h"
#include "FastLEDStrip.h"

using namespace rgb;

inline auto pixels = FastLEDStrip<300, D2_RGB>();

class RGBPatternApplication : public UserApplication<> {
protected:
  auto configure(RGBPatternApplication::Configurer& app) -> void override {
    app.addLEDs(pixels);
  }

  auto update() -> void override {

  }
  auto draw() -> void override {

  }

  auto postDraw() -> void override {
    for (int i = 0; i < pixels.length(); i++) {
      if (i % 3 == 0) {
        pixels.set(i, Color::RED() * .5f);
      }
      else if (i % 3 == 1) {
        pixels.set(i, Color::GREEN() * .5f);
      }
      else {
        pixels.set(i, Color::BLUE() * .5f);
      }
    }
  }
};


#endif //RGBLIB_RGBPATTERNAPPLICATION_H
