//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_OPTIMIZATIONAPPLICATION_H
#define RGBLIB_OPTIMIZATIONAPPLICATION_H

#include "VehicleApplication.h"
#include "Pin.h"
#include "IRReceiver.h"
#include "Timer.h"
#include "FastLEDStrip.h"
#include "FastLEDMatrix.h"
#include "NeopixelLEDStrip.h"
#include "GPIO.h"
#include "PixelStitch.h"
#include "ReversePixelList.h"
#include "ChasingEffect.h"
#include "DeadPixelList.h"
#include "PixelSlice.h"
#include "ChasingEffect.h"
#include "WipeEffect.h"

using namespace rgb;

auto s1 = FastLEDMatrix<8, 8, D2_RGB, RgbwSupport::ENABLE, 3, 2>();
auto wipeEffect = WipeEffect{};

class OptimizationApplication : public VehicleApplication<> {
protected:
  auto configure(VehicleApplication::Configurer& app) -> void override {
    s1.setBrightness(.1f);
    app.addLEDs(s1);

//    wipeEffect.shader = [](auto color, auto& params){
//      if (params.pixelPosition <= params.wipeLength) {
//        return Color::Sequential12(params.wipeCycle);
//      }
//      if (params.wipeCycle == 0) {
//        return Color::OFF();
//      }
//      else {
//        return Color::Sequential12(params.wipeCycle - 1);
//      }
//    };
//    wipeEffect.progression = EffectProgression::ConstantTime(Duration::Seconds(2));
//    Effects::Start(wipeEffect, s1).detach();

    app.useHeartbeatLED();
  }

  auto update() -> void override {
  }

  auto draw() -> void override {
    for (int row = 0; row < s1.rows(); ++row) {
      for (int col = 0; col < s1.columns(); ++col) {
        auto position = s1.columns() * row + col;
        auto f = position / static_cast<float>(s1.length());
        INFO("pos = %i", position);
        s1.set(position, Color::HslToRgb(f));
      }
    }
  }
};


#endif //RGBLIB_OPTIMIZATIONAPPLICATION_H
