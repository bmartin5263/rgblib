//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_SANDBOXAPPLICATION_H
#define RGBLIB_SANDBOXAPPLICATION_H

#include "Animations.h"
#include "UserApplication.h"
#include "ArrayAnimation.h"
#include "LEDStrip.h"
#include "ArrayGradient.h"

using namespace rgb;

inline auto strip = LEDStrip<40, D5_RGB>();
inline auto fiber = LEDStrip<130, D6_RGB>();
inline auto sunset = MirroredGradient(std::array {
  GradientStop{Color::BLUE()},
  GradientStop{Color::RED()},
  GradientStop{Color::ORANGE()},
});
inline auto ocean = MirroredGradient(std::array {
  GradientStop{Color::CYAN()},
  GradientStop{Color::BLUE()},
  GradientStop{Color::PURPLE()},
  GradientStop{Color::MAGENTA()},
});

inline auto animation = ArrayAnimation{ std::array {
  AnimationFrame{Duration::Seconds(1), [](auto&) {
    strip.fill(Color::RED());
  }},
  AnimationFrame{Duration::Seconds(1), [](auto&) {
    strip.fill(Color::GREEN());
  }},
  AnimationFrame{Duration::Seconds(1), [](auto&) {
    strip.fill(Color::BLUE());
  }},
  AnimationFrame::Once([](auto&) {
    INFO("Success!");
  }),
}};

class SandboxApplication : public UserApplication<> {
protected:
  auto configure(Configurer& app) -> void override {
    app.addPixels(strip);
    app.addPixels(fiber);
  }

  auto initialize() -> void override {
    Animations::Start(animation, true).detach();
  }

  auto postDraw() -> void override {
    strip.fill(sunset, Clock::Now().percentOfWrapped(Duration::Seconds(1)));
    fiber.fill(ocean, Clock::Now().percentOfWrapped(Duration::Seconds(1)));
  }
};


#endif //RGBLIB_SANDBOXAPPLICATION_H
