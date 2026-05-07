//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_SANDBOXAPPLICATION_H
#define RGBLIB_SANDBOXAPPLICATION_H

#include "UserApplication.h"
#include "FastLEDMatrix.h"
#include "WipeEffect.h"
#include "Every.h"
#include "RgbIIC.h"
#include "RTC.h"

using namespace rgb;

auto grid = FastLEDMatrix<8, 8, D2_RGB, RgbwSupport::ENABLE, 3, 2>();
auto wipeEffect = WipeEffect{};
auto lastUpdate = Timestamp{};

class SandboxApplication : public UserApplication<> {
protected:
  auto configure(UserApplication::Configurer& app) -> void override {
    RTC::Start();
    RTC::Adjust(DateTime(F(__DATE__), F(__TIME__)));

    grid.setBrightness(.2f);
    app.addLEDs(grid);
    app.useHeartbeatLED();

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
    wipeEffect.progression = EffectProgression::ConstantTime(Duration::Seconds(3));
    Effects::Start(wipeEffect, grid).detach();
  }

  auto update() -> void override {

  }

  auto draw() -> void override {
    if (every(Duration::Seconds(1), lastUpdate)) {
      auto rtcNow = RTC::Now();
      Serial.print(rtcNow.year());  Serial.print('/');
      Serial.print(rtcNow.month()); Serial.print('/');
      Serial.print(rtcNow.day());   Serial.print(" ");
      Serial.print(rtcNow.hour());  Serial.print(':');
      Serial.print(rtcNow.minute());Serial.print(':');
      Serial.println(rtcNow.second());
    }
  }

  auto postDraw() -> void override {
    grid.set(10, 0, Color::BLUE());
    grid.set(0, 10, Color::RED());
    grid.set(10, 10, Color::GREEN());
  }
};


#endif //RGBLIB_SANDBOXAPPLICATION_H
