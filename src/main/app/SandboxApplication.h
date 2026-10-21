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

inline auto ring = LEDMatrix<12, 12, D3_RGB, RgbwSupport::ENABLE>();
inline auto irReceiver = IRReceiver{PinNumber{7}};

class SandboxApplication : public UserApplication<> {
protected:
  auto configure(Configurer& app) -> void override {
    app.addPixels(ring);
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
    for (int i = 0; i < 12; i++) {
      ring.set(i, Color::Sequential12(i) * .5);
    }
  }
};


#endif //RGBLIB_SANDBOXAPPLICATION_H
