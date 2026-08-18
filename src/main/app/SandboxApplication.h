//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_SANDBOXAPPLICATION_H
#define RGBLIB_SANDBOXAPPLICATION_H

#include "Animations.h"
#include "UserApplication.h"
#include "ArrayAnimation.h"
#include "LEDStrip.h"
#include "LEDMatrix.h"
#include "LEDFiber.h"
#include "ArrayGradient.h"
#include "IRReceiver.h"

using namespace rgb;

inline auto strip = LEDStrip<40, D5_RGB>();
inline auto fiber = LEDFiber<130, D6_RGB>();
inline auto matrix = LEDMatrix<8, 8, D7_RGB>();
inline auto matrix2 = LEDMatrix<8, 8, D7_RGB>();
inline auto irReceiver = IRReceiver{PinNumber{7}};
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
inline auto animationHandle = AnimationHandle{};

class SandboxApplication : public UserApplication<> {
protected:
  auto configure(Configurer& app) -> void override {
    app.addPixels(strip);
    app.addPixels(fiber);
    app.addPixels(matrix);
    app.addPixels(matrix2);
    app.addSensor(irReceiver);

    app.on<IRButtonPressed>([](const IRButtonPressed& event) {
      switch (event.button) {
        case IRButtonType::BUTTON_1:
          break;
        case IRButtonType::BUTTON_2:
          break;
        case IRButtonType::BUTTON_3:
          break;
        case IRButtonType::BUTTON_4:
          break;
        case IRButtonType::BUTTON_5:
          break;
        case IRButtonType::BUTTON_6:
          break;
        case IRButtonType::BUTTON_7:
          break;
        case IRButtonType::BUTTON_8:
          break;
        case IRButtonType::BUTTON_9:
          break;
        case IRButtonType::BUTTON_0:
          break;
        case IRButtonType::BUTTON_UP:
          break;
        case IRButtonType::BUTTON_RIGHT:
          break;
        case IRButtonType::BUTTON_DOWN:
          break;
        case IRButtonType::BUTTON_LEFT:
          break;
        case IRButtonType::BUTTON_STAR:
          animationHandle = Animations::Start(animation, true);
          break;
        case IRButtonType::BUTTON_HASH:
          animationHandle = Animations::Start(animation, true);
          break;
        case IRButtonType::BUTTON_OK:
          animationHandle.stop();
          break;
      }
    });
  }

  auto initialize() -> void override {
    animationHandle = Animations::Start(animation, true);
  }

  auto postDraw() -> void override {
    // strip.fill(sunset, Clock::Now().percentOfWrapped(Duration::Seconds(1)));
    fiber.fill(ocean, Clock::Now().percentOfWrapped(Duration::Seconds(1)));
    matrix.fill(Color::HslToRgb(Clock::Now().percentOfWrapped(Duration::Seconds(1))));
    matrix2.fill(sunset);
  }
};


#endif //RGBLIB_SANDBOXAPPLICATION_H
