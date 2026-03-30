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
static constexpr rgb::u16 FIBER_STRIP_LED_COUNT = 150;
static constexpr rgb::u16 FULL_DASH_FIBER_LENGTH = FIBER_STRIP_LED_COUNT * 3;
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
auto dashFiber3Reverse = ReversePixelList(dashFiber3);

auto dashFiber12 = PixelStitch{dashFiber1, dashFiber2};
auto dashFiberFull = PixelStitch{dashFiber12, dashFiber3Reverse};

// Groups
auto footFiberGroup = std::array<PixelList*, 5> { &leftFoot, &rightFoot, &dashFiber1, &dashFiber2, &dashFiber3Reverse };

// Sensors
auto irRemote = IRReceiver{PinNumber{D3}};

// Effects

// Intro Effects
auto ringChase1 = ChasingEffect{};
auto ringChase2 = ChasingEffect{};
auto introWipe = WipeEffect{};

// Rpm Effect
auto rpmGauge = RpmGauge{};
auto footWipe = WipeEffect{};
auto fiberChase = ChasingEffectSpeedOnly{};


auto footTimerHandle = TimerHandle{};
auto footRainbowTimerHandle = TimerHandle{};

// Regular Level
auto footLevel = 0;
auto dashFiberLevel = 0;

// Rainbow Level
auto footRainbowLevel = 0;
auto dashFiberRainbowLevel = 0;

// Sleep Level
auto footSleepLevel = 0;
auto dashFiberSleepLevel = 0;

auto holdMode = false;
auto rainbowMode = false;
auto rpmGaugeHandle = EffectHandle{};
auto idleEffectHandle = EffectHandle{};

auto ringDebugColor = Color::OFF();

constexpr auto FOOT_PURPLE = Color {0.2f, 0.f, 1.0f};
constexpr auto FIBER_PURPLE = Color {0.3f, 0.f, 1.0f};
auto lowRpmColorFoot = FOOT_PURPLE;
auto lowRpmColorFiber = Color::GREEN();

auto levelUpFn = [](int& footLevel, int& dashFiberLevel){
  if (footLevel < leftFoot.length()) {
    ++footLevel;
  }
  ++dashFiberLevel;
  if (dashFiberLevel < dashFiber1.length()) {
    ++dashFiberLevel;
  }
  return footLevel < leftFoot.length() || dashFiberLevel < dashFiber1.length();
};
auto levelUpFn2 = [](int& footLevel, int& dashFiberLevel){
  if (footLevel < leftFoot.length()) {
    ++footLevel;
  }
  ++dashFiberLevel;
  if (dashFiberLevel < FULL_DASH_FIBER_LENGTH) {
    ++dashFiberLevel;
  }
  return footLevel < leftFoot.length() || dashFiberLevel < FULL_DASH_FIBER_LENGTH;
};
auto levelDownFn = [](int& footLevel, int& dashFiberLevel){
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
    Effects::Start(ringChase1, ring).detach();
//    Effects::Start(ringChase2, ringReverse).detach();
    Effects::Start(introWipe, footFiberGroup).detach();

    Timer::SetTimeout(Duration::Seconds(3), [](){
      INFO("Finished Intro Sequence");
      Effects::Stop(introWipe);
      Effects::Start(fiberChase, dashFiber1).detach();

      auto rpmRingChaseShader = [](Color highRpmColor) {
        return [highRpmColor](auto color, auto& params){
          auto& townCar = LincolnTownCar::Instance();
          auto rpm = townCar.smoothRpm();
          auto numerator = static_cast<float>(rpm) - LincolnTownCar::MAX_IDLE_RPM;
          constexpr auto denominator = LincolnTownCar::STARTING_RPM - LincolnTownCar::MAX_IDLE_RPM;
          auto t = numerator / denominator;
          auto myColor = Color::RED().lerpClamp(highRpmColor, t);
          return color + (myColor * params.brightness);
        };
      };

      ringChase1.shader = rpmRingChaseShader(Color::GREEN());
      ringChase2.shader = rpmRingChaseShader(FIBER_PURPLE);

    }).detach();
  }

protected:
  auto configure(Configurer& app) -> void override {
    ring.setOffset(11);

    app.addLEDs(ring);
    app.addLEDs(leftFoot);
    app.addLEDs(rightFoot);
    app.addLEDs(dashFiber1);
    app.addLEDs(dashFiber2);
    app.addLEDs(dashFiber3);
    app.addSensor(irRemote);

    ringChase1.buildup = true;
    ringChase1.shift = 3;
    ringChase1.progression = EffectProgression::ConstantTime(Duration::Milliseconds(400));
    ringChase1.trailLength = Length::Units(4);
    ringChase1.brightness = BrightnessLevels { .dim = .08f, .medium = .08f, .bright = .3f };
    ringChase1.shader = [](auto color, auto& params){
      return color + (Color::GREEN() * params.brightness);
    };

    ringChase2 = ringChase1;
    ringChase2.shift = 9;
    ringChase2.shader = [](auto color, auto& params){
      return color + (FIBER_PURPLE * params.brightness);
    };

    introWipe.progression = EffectProgression::ConstantTime(Duration::Milliseconds(500));
    introWipe.brightness = BrightnessLevels { .dim = .08f, .medium = .08f, .bright = .3f };
    introWipe.shader = [](auto pixel, auto& params){
      auto colorFunction = [](uint cycle){
        return (cycle % 2) == 0 ? Color::GREEN() : FOOT_PURPLE;
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
        return FOOT_PURPLE;
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
      Effects::Stop(ringChase1, ringChase2);
      if (!rpmGaugeHandle.isRunning()) {
        rpmGaugeHandle = Effects::Start(rpmGauge, ring);
      }

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
      if (holdMode) {
        return;
      }
      idleEffectHandle = Effects::Start(ringChase1, ring);
      Effects::Start(ringChase2, ringReverse).detach();
      rpmGaugeHandle.stop();
      ringDebugColor = Color::OFF();
      footTimerHandle = Timer::ContinuouslyWhile([](){ return levelDownFn(footLevel, dashFiberLevel); });
    });
    app.on<RainbowModeEntered>([](auto& event) {
      rpmGauge.startRainbow();
      footRainbowTimerHandle = Timer::ContinuouslyWhile([](){ return levelUpFn2(footRainbowLevel, dashFiberRainbowLevel); });
    });
    app.on<RainbowModeExited>([](auto& event) {
      rpmGauge.stopRainbow();
      footRainbowTimerHandle = Timer::ContinuouslyWhile([](){ return levelDownFn(footRainbowLevel, dashFiberRainbowLevel); });
    });


    app.on<IRButtonPressed>([](auto& event) {
      switch (event.button) {
        case IRButtonType::BUTTON_UP:
          Brightness::IncreaseLevel();
          TRACE("Button UP pressed");
          break;
        case IRButtonType::BUTTON_DOWN:
          Brightness::DecreaseLevel();
          TRACE("Button DOWN pressed");
          break;
        case IRButtonType::BUTTON_LEFT:
        case IRButtonType::BUTTON_RIGHT:
          TRACE("Button LEFT/RIGHT pressed");
          if (lowRpmColorFiber == Color::GREEN()) {
            lowRpmColorFiber = FIBER_PURPLE;
            lowRpmColorFoot = Color::GREEN();
          }
          else {
            lowRpmColorFoot = FOOT_PURPLE;
            lowRpmColorFiber = Color::GREEN();
          }
          break;
        case IRButtonType::BUTTON_0:
          TRACE("Button 0 pressed");
          holdMode = !holdMode;
          if (holdMode && LincolnTownCar::Instance().isStopped()) {
            LincolnApplication::PublishEvent(CarMoving{{Clock::Now()}, 0});
          }
          else if (!holdMode && LincolnTownCar::Instance().isStopped()) {
            LincolnApplication::PublishEvent(CarStopped{{Clock::Now()}});
          }
          break;
        case IRButtonType::BUTTON_9:
          TRACE("Button 9 pressed");
          rainbowMode = !rainbowMode;
          if (rainbowMode) {
            dashFiberRainbowLevel = FULL_DASH_FIBER_LENGTH;
            footRainbowLevel = FOOT_STRIP_LED_COUNT;
          }
          else {
            dashFiberRainbowLevel = 0;
            footRainbowLevel = 0;
          }
          break;
        default:
          INFO("Unknown Button Pressed");
      }
    });

//    app.on<OBDIIConnected>([this](auto& event){
//      if (isSleeping()) {
//        wakeUp();
//        RunIntroSequence();
//      }
//    });
//    app.on<OBDIIDisconnected>([this](auto& event){
//      goToSleep(Duration::Seconds(3));
//    });
//    app.on<SleepEvent>([](auto& event){
//      footRainbowTimerHandle = Timer::ContinuouslyWhile([](){ return levelUpFn(footSleepLevel, dashFiberSleepLevel); });
//    });
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
    dashFiber3Reverse.fill(Color::RED() * fiberBrightness);

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
    dashFiber3Reverse.fill(fiberRpmColor * fiberBrightness, dashFiberLevel);

    if (townCar.inRainbowMode() || rainbowMode) {
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

      auto dashFiberLedCount = FULL_DASH_FIBER_LENGTH;
      for (u16 level = 0; level < dashFiberLedCount && level < dashFiberRainbowLevel; ++level) {
        auto ratio = static_cast<float>(level) / static_cast<float>(dashFiberLedCount);
        auto rainbowDashColor = Color::HslToRgb(ratio);

        auto offset = Clock::Now().value / Duration::Milliseconds(10).value;
        auto index = (level + offset) % dashFiberLedCount;
//        dashFiber1.set(index, rainbowDashColor);
//        dashFiber2.set(index, rainbowDashColor);
//        dashFiber3Reverse.set(index, rainbowDashColor);
        dashFiberFull.set(index, rainbowDashColor);
        if (dashFiberRainbowLevel <= FULL_DASH_FIBER_LENGTH) {
          for (int i = 1; i <= 3 && static_cast<int>(dashFiberRainbowLevel) - i >= 0; ++i) {
//            dashFiber1.set(dashFiberRainbowLevel - i, Color::WHITE());
//            dashFiber2.set(dashFiberRainbowLevel - i, Color::WHITE());
//            dashFiber3Reverse.set(dashFiberRainbowLevel - i, Color::WHITE());
            dashFiberFull.set(dashFiberRainbowLevel - i, Color::WHITE());
          }
        }
      }
    }
  }

  auto postDraw() -> void override {
    leftFoot.fill(Color::OFF(), leftFoot.length() - footSleepLevel, leftFoot.length());
    rightFoot.fill(Color::OFF(), rightFoot.length() - footSleepLevel, rightFoot.length());
    dashFiber1.fill(Color::OFF(), dashFiber1.length() - dashFiberSleepLevel, dashFiber1.length());
    dashFiber2.fill(Color::OFF(), dashFiber2.length() - dashFiberSleepLevel, dashFiber2.length());
    dashFiber3Reverse.fill(Color::OFF(), dashFiber3Reverse.length() - dashFiberSleepLevel, dashFiber3Reverse.length());
  }
};


#endif //RGBLIB_LINCOLNAPPLICATION_H
