//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_LINCOLNAPPLICATION_H
#define RGBLIB_LINCOLNAPPLICATION_H

#include "FastLEDStrip.h"
#include "VehicleApplication.h"
#include "Pin.h"
#include "IRReceiver.h"
#include "Timer.h"
#include "GPIO.h"
#include "CustomEvents.h"
#include "PixelStitch.h"
#include "ReversePixelList.h"
#include "ChasingEffect.h"
#include "DeadPixelList.h"
#include "PixelSlice.h"
#include "ChasingEffect.h"
#include "ChasingEffectSpeedOnly.h"
#include "WipeEffect.h"
#include "Brightness.h"
#include "effect/RpmGauge.h"
#include "lincoln/LincolnTownCar.h"

using namespace rgb;

static constexpr rgb::u16 FOOT_STRIP_LED_COUNT = 40;
static constexpr rgb::u16 FIBER_STRIP_LED_COUNT = 146;
static constexpr rgb::u16 HALF_FOOT_STRIP_LED_COUNT = FOOT_STRIP_LED_COUNT / 2;

// LEDs
auto ring = FastLEDStrip<12, D2_RGB, RgbwSupport::ENABLE>();
auto leftFoot = FastLEDStrip<FOOT_STRIP_LED_COUNT, D4_RGB>();
auto rightFoot = FastLEDStrip<FOOT_STRIP_LED_COUNT, D5_RGB>();
auto dashFiber1 = FastLEDStrip<FIBER_STRIP_LED_COUNT, D6_RGB>();
auto dashFiber2 = FastLEDStrip<FIBER_STRIP_LED_COUNT, D7_RGB>();
auto dashFiber3 = FastLEDStrip<FIBER_STRIP_LED_COUNT, D8_RGB>();

// "Dead" Segments
auto deadHalfRing = DeadPixelList{ring.length() / 2};
auto deadFiberLength = DeadPixelList(dashFiber1.length());

// Segments
auto ringReverse = ReversePixelList{ring};
auto introRing = PixelStitch{ring, deadHalfRing};
auto introRingReverse = ReversePixelList{introRing};
auto heartBeatFiber = PixelStitch{dashFiber1, deadFiberLength};

// Groups
auto footGroup = std::array<PixelList*, 3> { &leftFoot, &rightFoot, &dashFiber1 };

// Sensors
auto irRemote = IRReceiver{PinNumber{D3}};

// Effects

// Intro Effects
auto introChase1 = ChasingEffect{};
auto introChase2 = ChasingEffect{};
auto introWipe = WipeEffect{};

// Rpm Effect
auto rpmGauge = RpmGauge{};
auto footWipe = WipeEffect{};
auto fiberChase = ChasingEffectSpeedOnly{};


auto footTimerHandle = TimerHandle{};
auto footRainbowTimerHandle = TimerHandle{};
auto footLevel = 0;
auto dashFiberLevel = 0;
auto footRainbowLevel = 0;
auto dashFiberRainbowLevel = 0;

auto ringDebugColor = Color::OFF();

constexpr auto FOOT_PURPLE = Color {0.2f, 0.f, 1.0f};
constexpr auto FIBER_PURPLE = Color {0.3f, 0.f, 1.0f};
auto lowRpmColorFoot = FOOT_PURPLE;
auto lowRpmColorFiber = Color::GREEN();

auto levelUpFn = [](int& footLevel, int& dashFiberLevel){
  INFO("%i, %i", footLevel, dashFiberLevel);
  if (footLevel < leftFoot.length()) {
    ++footLevel;
  }
  ++dashFiberLevel;
  if (dashFiberLevel < dashFiber1.length()) {
    ++dashFiberLevel;
  }
  return footLevel < leftFoot.length() || dashFiberLevel < dashFiber1.length();
};
auto levelDownFn = [](int& footLevel, int& dashFiberLevel){
  INFO("%i, %i", footLevel, dashFiberLevel);
  if (footLevel > 0) {
    --footLevel;
  }
  --dashFiberLevel;
  if (dashFiberLevel > 0) {
    --dashFiberLevel;
  }

  return footLevel > 0 || dashFiberLevel > 0;
};

class LincolnApplication : public VehicleApplication<HighwayModeEntered, HighwayModeExited> {
private:
  static auto RunIntroSequence() {
    INFO("Starting Intro Sequence");
    Effects::Start(introChase1, ring).detach();
    Effects::Start(introChase2, ringReverse).detach();
    Effects::Start(introWipe, footGroup).detach();

    Timer::SetTimeout(Duration::Seconds(3), [](){
      INFO("Finished Intro Sequence");
      Effects::Stop(introWipe);
      Effects::Start(fiberChase, heartBeatFiber).detach();

      introChase1.shader = [](auto color, auto& params){
        auto& townCar = LincolnTownCar::Instance();
        auto rpm = townCar.smoothRpm();
        auto numerator = static_cast<float>(rpm) - LincolnTownCar::MAX_IDLE_RPM;
        auto denominator = LincolnTownCar::STARTING_RPM - LincolnTownCar::MAX_IDLE_RPM;
        auto t = numerator / denominator;
        auto myColor = Color::RED().lerpClamp(Color::GREEN(), t);
        return color + (myColor * params.brightness);
      };
      introChase2.shader = [](auto color, auto& params){
        auto& townCar = LincolnTownCar::Instance();
        auto rpm = townCar.smoothRpm();
        auto numerator = static_cast<float>(rpm) - LincolnTownCar::MAX_IDLE_RPM;
        auto denominator = LincolnTownCar::STARTING_RPM - LincolnTownCar::MAX_IDLE_RPM;
        auto t = numerator / denominator;
        auto myColor = Color::RED().lerpClamp(FIBER_PURPLE, t);
        return color + (myColor * params.brightness);
      };

    }).detach();
  }

protected:
  auto configure(VehicleApplication::Configurer& app) -> void override {
    ring.setOffset(11);

    app.addLEDs(ring);
    app.addLEDs(leftFoot);
    app.addLEDs(rightFoot);
    app.addLEDs(dashFiber1);
    app.addLEDs(dashFiber2);
    app.addLEDs(dashFiber3);
    app.addSensor(irRemote);

    introChase1.buildup = true;
    introChase1.shift = 3;
    introChase1.progression = EffectProgression::ConstantTime(Duration::Milliseconds(1000));
    introChase1.trailLength = Length::Units(4);
    introChase1.brightness = BrightnessLevels { .dim = .08f, .medium = .08f, .bright = .3f };
    introChase1.shader = [](auto color, auto& params){
      return color + (Color::GREEN() * params.brightness);
    };
    introChase2 = introChase1;
    introChase2.shift = 9;
    introChase2.shader = [](auto color, auto& params){
      return color + (Color(.3f, 0.0f, 1.0f) * params.brightness);
    };
    introWipe.progression = EffectProgression::ConstantTime(Duration::Milliseconds(500));
    introWipe.shader = [](auto pixel, auto& params){
      auto colorFunction = [](uint cycle){
        return (cycle % 2) == 0 ? Color::GREEN() : Color{.2f, .0f, 1.0f};
      };
      if (params.pixelPosition <= params.wipeLength) {
        return colorFunction(params.wipeCycle);
      }
      else if (params.wipeCycle == 0) {
        return Color::OFF();
      }
      else {
        return colorFunction(params.wipeCycle - 1);
      }
    };
    footWipe.progression = EffectProgression::ConstantTime(Duration::Milliseconds(4000));
    footWipe.shader = [](auto pixel, auto& params){
      if (params.pixelPosition <= params.wipeLength || params.wipeCycle > 0) {
        return Color{.2f, .0f, 1.0f};
      }
      return pixel;
    };
    fiberChase.buildup = true;
    fiberChase.delay = Duration::Milliseconds(1);
    fiberChase.trailLength = Length::Units(60);
    fiberChase.shader = [](auto pixel, auto& params){
      return pixel * 1.5f;
    };

    app.on<WakeEvent>([](auto& event) { RunIntroSequence(); });

    app.on<CarMoving>([](auto& event){
      Effects::Stop(introChase1, introChase2);
      Effects::Start(rpmGauge, ring).detach();

      TRACE("Detected Car Moving!!");

      if (event.rpm < LincolnTownCar::STARTING_RPM + 500) {
        ringDebugColor = Color::RED();
      }
      else if (event.rpm < LincolnTownCar::STARTING_RPM + 700) {
        ringDebugColor = Color::ORANGE();
      }
      else if (event.rpm < LincolnTownCar::STARTING_RPM + 900) {
        ringDebugColor = Color::YELLOW();
      }
      else if (event.rpm < LincolnTownCar::STARTING_RPM + 1100) {
        ringDebugColor = Color::GREEN();
      }
      else if (event.rpm < LincolnTownCar::STARTING_RPM + 1300) {
        ringDebugColor = Color::BLUE();
      }
      else {
        ringDebugColor = Color::MAGENTA();
      }

      footTimerHandle = Timer::ContinuouslyWhile([](){ return levelUpFn(footLevel, dashFiberLevel); });
    });
    app.on<CarStopped>([](auto& event){
      Effects::Start(introChase1, ring).detach();
      Effects::Start(introChase2, ringReverse).detach();
      Effects::Stop(rpmGauge);
      ringDebugColor = Color::OFF();
      footTimerHandle = Timer::ContinuouslyWhile([](){ return levelDownFn(footLevel, dashFiberLevel); });
    });
    app.on<RainbowModeEntered>([](auto& event) {
      rpmGauge.startRainbow();
      footRainbowTimerHandle = Timer::ContinuouslyWhile([](){ return levelUpFn(footRainbowLevel, dashFiberRainbowLevel); });
    });
    app.on<RainbowModeExited>([](auto& event) {
      rpmGauge.stopRainbow();
      footRainbowTimerHandle = Timer::ContinuouslyWhile([](){ return levelDownFn(footRainbowLevel, dashFiberRainbowLevel); });
    });


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
        case IRButtonType::BUTTON_LEFT:
        case IRButtonType::BUTTON_RIGHT:
          INFO("Button LEFT/RIGHT pressed");
          if (lowRpmColorFiber == Color::GREEN()) {
            lowRpmColorFiber = FIBER_PURPLE;
            lowRpmColorFoot = Color::GREEN();
          }
          else {
            lowRpmColorFoot = FOOT_PURPLE;
            lowRpmColorFiber = Color::GREEN();
          }
          break;
        default:
          INFO("Unknown Button Pressed");
      }
    });
  }

  auto update() -> void override {
    constexpr auto NINTY_MPH = 144.f;

    auto& townCar = LincolnTownCar::Instance();
    townCar.update();

    auto speed = static_cast<float>(townCar.smoothSpeed());
    auto chaseTime = Duration::Microseconds(LerpClamp(10000, 2000, speed / NINTY_MPH));
    fiberChase.delay = chaseTime;
  }

  auto draw() -> void override {
    auto& townCar = LincolnTownCar::Instance();

    static uint level1 = 0;
    static uint level2 = 0;

    auto highRpmColor = Color::RED();

    auto fiberBrightness = Brightness::GetBrightness({
      .dim = .2f,
      .medium = .4f,
      .bright = .7f,
      .max = 1.0f
    });

    leftFoot.fill(Color::RED());
    rightFoot.fill(Color::RED());
    dashFiber1.fill(Color::RED() * fiberBrightness);
    dashFiber2.fill(Color::RED() * fiberBrightness);
    dashFiber3.fill(Color::RED() * fiberBrightness);

    if (townCar.inRainbowMode()) {
      auto t = Clock::Now().percentOfWrapped(Duration::Seconds(1));
      auto color = Color::HslToRgb(t);
      auto footLedCount = leftFoot.length();

      for (u16 level = 0; level < footLedCount && level < footLevel && level < footRainbowLevel; ++level) {
        auto ratio = static_cast<float>(level) / static_cast<float>(footLedCount);
        auto rainbowFootColor = Color::HslToRgb(ratio);

        auto offset = Clock::Now().value / Duration::Milliseconds(50).value;
        auto index = (level + offset) % footLedCount;
        leftFoot.set(index, rainbowFootColor);
        rightFoot.set(index, rainbowFootColor);
        if (footRainbowLevel <= leftFoot.length()) {
          for (int i = 1; i <= 3 && static_cast<int>(footRainbowLevel) - i >= 0; ++i) {
            leftFoot.set(footRainbowLevel - i, Color::FAKE_WHITE());
            rightFoot.set(footRainbowLevel - i, Color::FAKE_WHITE());
          }
        }
      }

      dashFiber1.fill(color * fiberBrightness);
      dashFiber2.fill(color * fiberBrightness);
      dashFiber3.fill(color * fiberBrightness);
    }
    else {
      auto rpm = townCar.smoothRpm();
      auto start = 1500.0f;
      auto max = 2500.0f;
      auto time = (rpm - start) / (max - start);

      auto footRpmColor = lowRpmColorFoot.lerpClamp(highRpmColor, time);
      auto fiberRpmColor = lowRpmColorFiber.lerpClamp(highRpmColor, time);

      leftFoot.fill(footRpmColor, footLevel);
      rightFoot.fill(footRpmColor, footLevel);

      dashFiber1.fill(fiberRpmColor * fiberBrightness, dashFiberLevel);
      dashFiber2.fill(fiberRpmColor * fiberBrightness, dashFiberLevel);
      dashFiber3.fill(fiberRpmColor * fiberBrightness, dashFiberLevel);
    }
  }

  auto postDraw() -> void override {
//    if (ringDebugColor != Color::OFF()) {
//      ring.set(10, ringDebugColor * .03f);
//    }
  }
};


#endif //RGBLIB_LINCOLNAPPLICATION_H
