//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_CORVETTEMETALARTAPPLICATION_H
#define RGBLIB_CORVETTEMETALARTAPPLICATION_H

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
auto s1 = FastLEDStrip<90, D2_RGB>();
auto irRemote = IRReceiver{PinNumber{D3}};
auto chaseEffect = ChasingEffect{};
auto wipeEffect = WipeEffect{};

auto deadLongPixelList = DeadPixelList{40};
auto deadShortPixelList = DeadPixelList{16};
auto rightShort = s1.slice(12);
auto rightShortLonger = PixelStitch{rightShort, deadShortPixelList};
auto rightLong = s1.slice(12, 44);
auto rightLonger = PixelStitch{deadLongPixelList, rightLong};
auto rightLongerReverse = ReversePixelList{rightLonger};
auto leftLong = s1.slice(44, 76);
auto leftLonger = PixelStitch{leftLong, deadLongPixelList};
auto leftShort = s1.slice(76, 88);
auto leftShortLonger = PixelStitch{deadShortPixelList, leftShort};
auto leftShortLongerReverse = ReversePixelList{leftShortLonger};
auto longGroup = std::array<PixelList*, 4> { &leftLonger, &rightLongerReverse, &leftShortLongerReverse, &rightShortLonger };

auto leftLongRev = ReversePixelList{leftLong};
auto leftShortRev = ReversePixelList{leftShort};
auto leftSegmentTemp = PixelStitch{leftShortRev, leftLongRev};
auto rightSegmentTemp = PixelStitch{rightShort, rightLong};
auto leftSegment = PixelStitch{leftSegmentTemp, deadLongPixelList};
auto rightSegment = PixelStitch{rightSegmentTemp, deadLongPixelList};
auto wipeGroup = std::array<PixelList*, 2> { &leftSegment, &rightSegment };

class CorvetteMetalArtApplication : public VehicleApplication<> {
protected:
  auto configure(VehicleApplication::Configurer& app) -> void override {
    s1.setBrightness(.8f);
    app.addLEDs(s1);
    app.addSensor(irRemote);

//    chaseEffect.shader = [](auto color, auto& params){
//      return Color::GREEN() * brightness;
//    };
//    chaseEffect.trailLength = Length::Ratio(.5f);
//    Effects::Start(chaseEffect, longGroup).detach();

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
    wipeEffect.progression = EffectProgression::ConstantTime(Duration::Seconds(2));
    Effects::Start(wipeEffect, wipeGroup).detach();

    app.on<IRButtonPressed>([](auto& event) {
      switch (event.button) {
        case IRButtonType::BUTTON_LEFT:
          break;
        case IRButtonType::BUTTON_RIGHT:
          break;
        case IRButtonType::BUTTON_DOWN:
          break;
        case IRButtonType::BUTTON_UP:
          break;
        default:
          INFO("Unknown Button Pressed");
      }
    });
  }

  auto update() -> void override {
  }

  auto draw() -> void override {
//    auto t = Clock::Now().percentOfWrapped(Duration::Seconds(10));
//    s1.fill(Color::HslToRgb(t));
//    s1.fill(Color::PURPLE() * brightness, 12);
//    s1.fill(Color::PURPLE() * brightness, 12, 44);
//    s1.fill(Color::PURPLE() * brightness, 44, 76);
//    s1.fill(Color::PURPLE() * brightness, 76, 88);
//
//    auto pulse = Pulse(Clock::Now(), Duration::Seconds(2));
//    auto blue = Color(0.0f, .5f, 1.0f) * .1f;
//    auto pink = Color(1.0f, 0.0f, .2f) * .1f;
//    s1.fill(blue.lerpClamp(pink, pulse));
//    s1.fill(Color::BLUE());
  }
};


#endif //RGBLIB_CORVETTEMETALARTAPPLICATION_H
