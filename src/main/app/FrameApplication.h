//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_FRAMEAPPLICATION_H
#define RGBLIB_FRAMEAPPLICATION_H

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
auto s1 = FastLEDStrip<100, D2_RGB>();
auto s2 = FastLEDStrip<7, D4_RGB, RgbwSupport::ENABLE>();
auto s3 = FastLEDStrip<8, D5_RGB>();

auto irRemote = IRReceiver{PinNumber{D3}};

auto chasingEffect = ChasingEffect{};

uint start = 10;
uint range = 30;

class FrameApplication : public VehicleApplication<> {
protected:
  auto configure(VehicleApplication::Configurer& app) -> void override {
    app.addLEDs(s1);
    app.addLEDs(s2);
    app.addLEDs(s3);
    app.addSensor(irRemote);

//    chasingEffect.shader = [](auto color, const auto& params){
//      return Color::Sequential12(params.cycle) * .03;
//    };
//    chasingEffect.trailLength = Length::Ratio(.5f);
//    chasingEffect.progression = EffectProgression::ConstantSpeed(Duration::Seconds(1));
//    Effects::Start(chasingEffect, s1).detach();

    app.on<IRButtonPressed>([](auto& event) {
      switch (event.button) {
        case IRButtonType::BUTTON_LEFT:
          if (start > 0) {
            --start;
          }
          break;
        case IRButtonType::BUTTON_RIGHT:
          ++start;
          break;
        case IRButtonType::BUTTON_DOWN:
          if (range > 0) {
            --range;
          }
          break;
        case IRButtonType::BUTTON_UP:
          ++range;
          break;
        default:
          INFO("Unknown Button Pressed");
      }
    });
  }

  auto update() -> void override {
  }

  auto draw() -> void override {
    auto minRed = Color::RED() * .3f;
    auto maxRed = Color::RED() * .8f;
    auto master = .5f;

    s1.fill(Color::BLUE() * master, start, start + range);
    s3.fill(Color(.2f, 0.0f, 1.0f) * master);
    s2.fill(minRed.lerpClamp(maxRed, Pulse(Clock::Now(), Duration::Seconds(1))) * master);

    auto length = static_cast<uint>(10 * Clock::Now().percentOfWrapped(Duration::Seconds(1)));
    s3.fill(Color(0.f, 1.0f, 0.1f) * master, length);
  }
};


#endif //RGBLIB_FRAMEAPPLICATION_H
