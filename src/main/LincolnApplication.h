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
#include "WipeEffect.h"
#include "Brightness.h"
#include "RpmEffect.h"

using namespace rgb;

static constexpr rgb::u16 FOOT_STRIP_LED_COUNT = 40;
static constexpr rgb::u16 FIBER_STRIP_LED_COUNT = 410;
static constexpr rgb::u16 HALF_FOOT_STRIP_LED_COUNT = FOOT_STRIP_LED_COUNT / 2;

// LEDs
auto ring = FastLEDStrip<12, D2_RGB, RgbwSupport::ENABLE>();
auto ringReverse = ReversePixelList{ring};
auto deadHalfRing = DeadPixelList{ring.length() / 2};
auto introRing = PixelStitch{ring, deadHalfRing};
auto introRingReverse = ReversePixelList{introRing};


auto leftFoot = FastLEDStrip<FOOT_STRIP_LED_COUNT, D4_RGB>();
auto rightRoot = FastLEDStrip<FOOT_STRIP_LED_COUNT, D5_RGB>();
auto dashFiber = FastLEDStrip<FIBER_STRIP_LED_COUNT, D6_RGB>();

// Sensors
auto irRemote = IRReceiver{PinNumber{D3}};

// Effects
auto chasingEffect1 = ChasingEffect{};
auto chasingEffect2 = ChasingEffect{};
auto chasingEffectHandle = EffectHandle{};

auto rpmEffect = RpmEffect{};
auto rpmEffectHandle = EffectHandle{};

class LincolnApplication : public VehicleApplication<HighwayModeEntered, HighwayModeExited> {
protected:
  auto configure(VehicleApplication::Configurer& app) -> void override {

    app.addLEDs(ring);
    app.addLEDs(leftFoot);
    app.addLEDs(rightRoot);
    app.addLEDs(dashFiber);
    app.addSensor(irRemote);

    app.on<WakeEvent>([](auto& event) {
      chasingEffect1.buildup = true;
      chasingEffect1.shift = 3;
      chasingEffect1.progression = EffectProgression::ConstantTime(Duration::Milliseconds(1000));
      chasingEffect1.trailLength = Length::Units(4);
      chasingEffect1.brightness = BrightnessLevels {
        .dim = .03f,
      };
      chasingEffect1.shader = [](auto color, auto& params){
        return color + (Color::GREEN() * params.brightness);
      };
      chasingEffect2.buildup = true;
      chasingEffect2.shift = 9;
      chasingEffect2.progression = EffectProgression::ConstantTime(Duration::Milliseconds(1000));
      chasingEffect2.trailLength = Length::Units(4);
      chasingEffect2.brightness = BrightnessLevels {
        .dim = .03f,
      };
      chasingEffect2.shader = [](auto color, auto& params){
        return color + (Color(.3f, 0.0f, 1.0f) * params.brightness);
      };
      Effects::Start(chasingEffect1, ring).detach();
      Effects::Start(chasingEffect2, ringReverse).detach();

      Timer::SetTimeout(Duration::Seconds(400), [](){
        Effects::Stop(chasingEffect1);
        Effects::Stop(chasingEffect2);
        rpmEffectHandle = Effects::Start(rpmEffect, ring);
      }).detach();
    });
    app.on<OBDIIConnected>([](auto& event){
    });
    app.on<OBDIIDisconnected>([](auto& event){
    });
    app.on<HighwayModeEntered>([](auto& event){

    });
    app.on<HighwayModeExited>([](auto& event){

    });

    app.on<IRButtonPressed>([](auto& event) {
      switch (event.button) {
        case IRButtonType::BUTTON_1: INFO("Button 1 pressed"); break;
        case IRButtonType::BUTTON_2: INFO("Button 2 pressed"); break;
        case IRButtonType::BUTTON_3: INFO("Button 3 pressed"); break;
        case IRButtonType::BUTTON_4: INFO("Button 4 pressed"); break;
        case IRButtonType::BUTTON_5: INFO("Button 5 pressed"); break;
        case IRButtonType::BUTTON_6: INFO("Button 6 pressed"); break;
        case IRButtonType::BUTTON_7: INFO("Button 7 pressed"); break;
        case IRButtonType::BUTTON_8: INFO("Button 8 pressed"); break;
        case IRButtonType::BUTTON_9: INFO("Button 9 pressed"); break;
        case IRButtonType::BUTTON_0: INFO("Button 0 pressed"); break;
        case IRButtonType::BUTTON_STAR: INFO("Button * pressed"); break;
        case IRButtonType::BUTTON_HASH: INFO("Button # pressed"); break;
        case IRButtonType::BUTTON_UP:
          Brightness::IncreaseLevel();
          INFO("Button UP pressed");
          break;
        case IRButtonType::BUTTON_DOWN:
          Brightness::DecreaseLevel();
          INFO("Button DOWN pressed");
          break;
        case IRButtonType::BUTTON_LEFT: INFO("Button LEFT pressed"); break;
        case IRButtonType::BUTTON_RIGHT: INFO("Button RIGHT pressed"); break;
        case IRButtonType::BUTTON_OK: INFO("Button OK pressed"); break;
        default:
          INFO("Unknown Button Pressed");
      }
    });
  }

  auto update() -> void override {

  }

  auto draw() -> void override {
    leftFoot.fill(Color::RED());
//    ring.fill(Color::GREEN() * .03f);
    rightRoot.fill(Color::BLUE());
    dashFiber.fill(Color::MAGENTA());
  }
};


#endif //RGBLIB_LINCOLNAPPLICATION_H
