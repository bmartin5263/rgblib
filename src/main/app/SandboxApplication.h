//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_SANDBOXAPPLICATION_H
#define RGBLIB_SANDBOXAPPLICATION_H

#include "UserApplication.h"
#include "LEDStrip.h"
#include "LEDMatrix.h"
#include "LEDFiber.h"
#include "ArrayGradient.h"
#include "IRReceiver.h"

using namespace rgb;

// inline auto ring = LEDStrip<12, D2_RGB, RgbwSupport::ENABLE>();
inline auto irReceiver = IRReceiver{PinNumber{A7}};

// LEDs
using TachometerStrip = rgb::LEDStrip<12, D2_RGB, rgb::RgbwSupport::ENABLE>;
using LeftFootStrip = rgb::LEDStrip<30, D4_RGB>;
using RightFootStrip = rgb::LEDStrip<30, D5_RGB>;
using LongFiberStrip1 = rgb::LEDFiber<30, D6_RGB>;
using LongFiberStrip2 = rgb::LEDFiber<30, D7_RGB>;
using ShortFiberStrip = rgb::LEDFiber<30, D8_RGB>;

// LEDs
inline auto ring = TachometerStrip{};
inline auto leftFoot = LeftFootStrip{};
inline auto rightFoot = RightFootStrip{};
inline auto dashFiber1 = LongFiberStrip1{};
inline auto dashFiber2 = LongFiberStrip2{};
inline auto dashFiber3 = ShortFiberStrip{};

class SandboxApplication : public UserApplication<> {
protected:
  auto configure(Configurer& app) -> void override {
    app.addPixels(ring);
    app.addPixels(leftFoot);
    app.addPixels(rightFoot);
    app.addPixels(dashFiber1);
    app.addPixels(dashFiber2);
    app.addPixels(dashFiber3);
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
          break;
        case IRButtonType::BUTTON_HASH:
          break;
        case IRButtonType::BUTTON_OK:
          break;
      }
    });
  }

  auto postDraw() -> void override {
    for (int i = 0; i < ring.size(); i++) {
      ring.set(i, Color::Sequential12(i) * .5);
    }
    for (int i = 0; i < leftFoot.size(); i++) {
      leftFoot.set(i, Color::Sequential12(i) * .5);
    }
    for (int i = 0; i < rightFoot.size(); i++) {
      rightFoot.set(i, Color::Sequential12(i) * .5);
    }
    for (int i = 0; i < dashFiber1.size(); i++) {
      dashFiber1.set(i, Color::Sequential12(i) * .5);
    }
    for (int i = 0; i < dashFiber2.size(); i++) {
      dashFiber2.set(i, Color::Sequential12(i) * .5);
    }
  }
};


#endif //RGBLIB_SANDBOXAPPLICATION_H
