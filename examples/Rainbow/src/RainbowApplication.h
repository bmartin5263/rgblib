//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_RAINBOWAPPLICATION_H
#define RGBLIB_RAINBOWAPPLICATION_H

#include "UserApplication.h"
#include "FastLEDStrip.h"
#include "ChaseEffect.h"

using namespace rgb;

static constexpr auto LED_COUNT = 40;
static constexpr auto LED_PIN = D5;

inline auto ledStrip = FastLEDStrip<40, LED_PIN, RgbwSupport::ENABLE>();
inline auto chaseEffect = ChaseEffect{};
inline auto chaseEffectHandle = EffectHandle{};

class RainbowApplication : public UserApplication<> {
protected:

  auto configure(Configurer& app) -> void override {
    INFO("Configuring Application");

    ledStrip.setBrightness(.2f);
    app.addLEDs(ledStrip);
    app.on<AppReady>([](auto&) {
      chaseEffectHandle = Effects::Start(chaseEffect, ledStrip);
    });
  }

  auto initialize() -> void override {
    chaseEffect.progression = EffectProgression::ConstantTime(Duration::Seconds(1));
    chaseEffect.trailLength = Length::Ratio(.2f);
    chaseEffect.shader = [](auto pixel, auto& params) {
      return pixel * 2.0f; // double the brightness
    };
  }

  auto draw() -> void override {
    auto time = Clock::Now().percentOfWrapped(Duration::Seconds(5)); // 0.0 - 1.0f
    auto color = Color::HslToRgb(time); // Cycles through rainbow given a value 0-1
    ledStrip.fill(color);
  }
};

#endif //RGBLIB_RAINBOWAPPLICATION_H
