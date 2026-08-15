//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_SANDBOXAPPLICATION_H
#define RGBLIB_SANDBOXAPPLICATION_H

#include "Animations.h"
#include "UserApplication.h"
#include "FastLEDMatrix.h"
#include "ArrayAnimation.h"
#include "FastLEDStrip.h"

using namespace rgb;

inline auto strip = FastLEDStrip<40, D2_RGB, RgbwSupport::ENABLE>();

inline auto animation = ArrayAnimation{ std::array {
  AnimationFrame{Duration::Seconds(1), [](auto& ctx) {
    strip.fill(Color::RED());
  }},
  AnimationFrame{Duration::Seconds(1)},
  AnimationFrame{Duration::Seconds(1), [](auto& ctx) {
    strip.fill(Color::GREEN());
  }},
  AnimationFrame{Duration::Seconds(1)},
  AnimationFrame{Duration::Seconds(1), [](auto& ctx) {
    strip.fill(Color::BLUE());
  }},
  AnimationFrame{Duration::Seconds(1)},
}};

class SandboxApplication : public UserApplication<> {
protected:
  auto configure(Configurer& app) -> void override {
    app.addLEDs(strip);
  }

  auto initialize() -> void override {
    Animations::Start(animation, true).detach();
  }

  auto postDraw() -> void override {
  }
};


#endif //RGBLIB_SANDBOXAPPLICATION_H
