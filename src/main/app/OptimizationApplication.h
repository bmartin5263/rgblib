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

auto s1 = FastLEDStrip<100, D2_RGB>();

class OptimizationApplication : public VehicleApplication<> {
protected:
  auto configure(VehicleApplication::Configurer& app) -> void override {
    app.addLEDs(s1);
  }

  auto update() -> void override {
  }

  auto draw() -> void override {
  }
};


#endif //RGBLIB_OPTIMIZATIONAPPLICATION_H
