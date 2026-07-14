//
// Created by Brandon on 7/13/26.
//

#ifndef RGBLIB_CORVETTEMAIN_H
#define RGBLIB_CORVETTEMAIN_H

#include "CorvetteApp.h"
#include "UserApplication.h"
#include "FastLEDStrip.h"
#include "Corvette.h"
#include "effect/RpmGauge.h"

using namespace rgb;

// LEDs
inline LeftFootStrip leftFoot = LeftFootStrip();
inline RightFootStrip rightFoot = RightFootStrip();
inline TachometerStrip tachometer = TachometerStrip();
inline CenterFiberStrip centerFiber = CenterFiberStrip();

inline auto rpmGauge = RpmGauge{};

class CorvetteApplication : public UserApplication<CorvetteAppEvents> {
protected:

  auto configure(Configurer& app) -> void override {
    app.addLEDs(leftFoot);
    app.addLEDs(rightFoot);
    app.addLEDs(tachometer);
    app.addLEDs(centerFiber);

    Corvette::Instance().init();

    rpmGauge.shape = RpmShape::LINE;
    rpmGauge.yellowLineStart = 3400;
    rpmGauge.redLineStart = 3800;
    rpmGauge.limit = 4000;
    rpmGauge.rpmStart = 1000;
    rpmGauge.minCoolantLevel = 70.f;
    rpmGauge.maxCoolantLevel = 150.f;
    rpmGauge.pulseBrightnessScale = 2.5f;
    rpmGauge.smoothRpmSupplier = [] { return Corvette::Instance().smoothRpm(); };
    rpmGauge.coolantTempSupplier = [] { return Corvette::Instance().coolantTemp(); };
    rpmGauge.rainbowSupplier = [] { return Corvette::Instance().inRainbowMode(); };
    rpmGauge.glowCondition = GlowCondition::RED_LINE;
    Effects::Start(rpmGauge, tachometer).detach();
  }

  auto update() -> void override {
    Corvette::Instance().update();
  }

  auto draw() -> void override {
    Corvette::Instance().draw();
  }
};

#endif //RGBLIB_CORVETTEMAIN_H
