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
#include "NeopixelLEDStrip.h"
#include "GPIO.h"
#include "CustomEvents.h"
#include "PixelStitch.h"
#include "ReversePixelList.h"
#include "ChasingEffect.h"
#include "DeadPixelList.h"
#include "PixelSlice.h"
#include "ChasingEffect.h"
#include "WipeEffect.h"

using namespace rgb;

auto s1 = FastLEDStrip<360, D2_RGB>();
auto wipeEffect = WipeEffect{};

class OptimizationApplication : public VehicleApplication<> {
protected:
  auto configure(VehicleApplication::Configurer& app) -> void override {
    s1.setBrightness(.8f);
    app.addLEDs(s1);

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
    wipeEffect.progression = EffectProgression::ConstantTime(Duration::Seconds(2));
    Effects::Start(wipeEffect, s1).detach();

    app.useHeartbeatLED();
  }

  auto update() -> void override {

  }

  auto draw() -> void override {
  }
};


#endif //RGBLIB_OPTIMIZATIONAPPLICATION_H
