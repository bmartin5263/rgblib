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

// LEDs
auto s1 = NeopixelLEDStrip<12, 5, NEO_GRBW + NEO_KHZ800>();
//auto s2 = NeopixelLEDStrip<40, 6, NEO_GRBW + NEO_KHZ800>();
//auto s3 = NeopixelLEDStrip<40, 7, NEO_GRBW + NEO_KHZ800>();
//auto s4 = NeopixelLEDStrip<135, 8, NEO_GRBW + NEO_KHZ800>();
//auto s5 = NeopixelLEDStrip<135, 9, NEO_GRBW + NEO_KHZ800>();
//auto s6 = NeopixelLEDStrip<135, 10, NEO_GRBW + NEO_KHZ800>();
//auto s7 = NeopixelLEDStrip<135, 17, NEO_GRBW + NEO_KHZ800>();
//auto s8 = NeopixelLEDStrip<135, 18, NEO_GRBW + NEO_KHZ800>();
//auto s9 = NeopixelLEDStrip<135, 21, NEO_GRBW + NEO_KHZ800>();
//auto s10 = NeopixelLEDStrip<135, 38, NEO_GRBW + NEO_KHZ800>();
auto irRemote = IRReceiver{PinNumber{D12}};
auto wipeEffect = WipeEffect{};
auto eHandle = EffectHandle{};
auto group = std::array<PixelList*, 0> {
//  &s1,
//  &s2,
//  &s3,
//  &s4,
//  &s5,
//  &s6,
//  &s7,
//  &s8,
//  &s9,
//  &s10
};

class OptimizationApplication : public VehicleApplication<> {
protected:
  auto configure(VehicleApplication::Configurer& app) -> void override {
    /**
     * These LEDs will be redrawn every frame draw()
     */
    app.addLEDs(s1);
//    app.addLEDs(s2);
//    app.addLEDs(s3);
//    app.addLEDs(s4);
//    app.addLEDs(s5);
//    app.addLEDs(s6);
//    app.addLEDs(s7);
//    app.addLEDs(s8);
//    app.addLEDs(s9);
//    app.addLEDs(s10);
    app.addSensor(irRemote);

    eHandle = Effects::Start(wipeEffect, group);

    app.on<IRButtonPressed>([](auto& event) {
      switch (event.button) {
        case IRButtonType::BUTTON_UP:
          Brightness::IncreaseLevel();
          INFO("Button UP pressed");
          break;
        case IRButtonType::BUTTON_DOWN:
          Brightness::DecreaseLevel();
          INFO("Button DOWN pressed");
          break;
        default:
          break;
      }
    });
  }

  auto update() -> void override {

  }

  auto draw() -> void override {

  }
};


#endif //RGBLIB_OPTIMIZATIONAPPLICATION_H
