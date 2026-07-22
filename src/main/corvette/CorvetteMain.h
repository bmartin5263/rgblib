//
// Created by Brandon on 7/13/26.
//

#ifndef RGBLIB_CORVETTEMAIN_H
#define RGBLIB_CORVETTEMAIN_H

#include "CorvetteApp.h"
#include "UserApplication.h"
#include "FastLEDStrip.h"
#include "Corvette.h"
#include "IRReceiver.h"
#include "effect/RpmGauge.h"

using namespace rgb;

// LEDs
inline LeftFootStrip leftFoot = LeftFootStrip();
inline RightFootStrip rightFoot = RightFootStrip();
inline TachometerStrip tachometer = TachometerStrip();
inline CenterFiberStrip centerFiber = CenterFiberStrip();
inline LeftFiberStrip leftFiber = LeftFiberStrip();
inline RightFiberStrip rightFiber = RightFiberStrip();

// Sensors
inline auto irReceiver = IRReceiver{PinNumber{A7}};

// Effects
inline auto rpmGauge = RpmGauge{};
inline auto rpmGaugeHandle = EffectHandle{};

class CorvetteApplication : public UserApplication<CorvetteAppEvents> {
protected:

  auto configure(Configurer& app) -> void override {
    leftFiber.setReversed(true);
    rightFiber.setReversed(true);

    app.addLEDs(leftFoot);
    app.addLEDs(rightFoot);
    app.addLEDs(tachometer);
    app.addLEDs(centerFiber);
    app.addLEDs(leftFiber);
    app.addLEDs(rightFiber);
    app.addSensor(irReceiver);

    Corvette::Instance().setup();
    app.on<VehicleDisconnected>([](auto& event) {
      auto& corvette = Corvette::Instance();
      if (!corvette.isSleeping() && corvette.speed() == 0) {
        corvette.transitionToSleeping();
        rpmGaugeHandle.stop();
      }
    });
    app.on<VehicleConnected>([](auto& event) {
      auto& corvette = Corvette::Instance();
      if (corvette.isSleeping()) {
        corvette.transitionToColdStart();
        rpmGaugeHandle = Effects::Start(rpmGauge, tachometer);
      }
    });
    app.on<IRButtonPressed>([](auto& event) {
      switch (event.button) {
        case IRButtonType::BUTTON_UP:
          Brightness::IncreaseLevel();
          break;
        case IRButtonType::BUTTON_DOWN:
          Brightness::DecreaseLevel();
          break;
        case IRButtonType::BUTTON_1:
          Corvette::Instance().toggleHoldMode();
          break;
        default:
          break;
      }
    });

    rpmGauge.shape = RpmShape::LINE;
    rpmGauge.yellowLineStart = 3400;
    rpmGauge.redLineStart = 3800;
    rpmGauge.limit = 4000;
    rpmGauge.rpmStart = 1000;
    rpmGauge.minCoolantLevel = 70.f;
    rpmGauge.maxCoolantLevel = 170.f;
    rpmGauge.pulseBrightnessScale = 2.5f;
    rpmGauge.smoothRpmSupplier = [] { return Corvette::Instance().smoothRpm(); };
    rpmGauge.coolantTempSupplier = [] { return Corvette::Instance().coolantTemp(); };
    rpmGauge.rainbowSupplier = [] { return Corvette::Instance().inRainbowMode(); };
    rpmGauge.glowCondition = GlowCondition::RED_LINE;
  }

  auto initialize() -> void override {
    Brightness::SetLevel(BrightnessLevel::MEDIUM);
    Corvette::Instance().init();
    rpmGaugeHandle = Effects::Start(rpmGauge, tachometer);
  }

  auto update() -> void override {
    Corvette::Instance().update();
  }

  auto draw() -> void override {
    Corvette::Instance().draw();
  }
};

#endif //RGBLIB_CORVETTEMAIN_H
