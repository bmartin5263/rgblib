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
#include "RTClib.h"

using namespace rgb;

auto grid = FastLEDMatrix<8, 8, D2_RGB, RgbwSupport::ENABLE, 3, 2>();
auto wipeEffect = WipeEffect{};
auto rtc = RTC_DS3231{};
auto lastUpdate = Timestamp{};

class SandboxApplication : public UserApplication<> {
protected:
  auto configure(UserApplication::Configurer& app) -> void override {
    IIC::Start();

    rtc.begin();
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

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
    if (Clock::Now().timeSince(lastUpdate) > Duration::Seconds(1)) {
      auto now = rtc.now();
      Serial.print(now.year());  Serial.print('/');
      Serial.print(now.month()); Serial.print('/');
      Serial.print(now.day());   Serial.print(" ");
      Serial.print(now.hour());  Serial.print(':');
      Serial.print(now.minute());Serial.print(':');
      Serial.println(now.second());
      lastUpdate = Clock::Now();
    }
  }

  auto postDraw() -> void override {
    grid.set(10, 0, Color::BLUE());
    grid.set(0, 10, Color::RED());
    grid.set(10, 10, Color::GREEN());
  }
};


#endif //RGBLIB_SANDBOXAPPLICATION_H
