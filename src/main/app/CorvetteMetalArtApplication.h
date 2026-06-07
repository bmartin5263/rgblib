//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_CORVETTEMETALARTAPPLICATION_H
#define RGBLIB_CORVETTEMETALARTAPPLICATION_H

#include "UserApplication.h"
#include "Pin.h"
#include "IRReceiver.h"
#include "Timer.h"
#include "FastLEDStrip.h"
#include "NeopixelLEDStrip.h"
#include "GPIO.h"
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
auto wipeEffect = WipeEffect{};

auto deadLongPixelList = DeadPixelList{40};
auto rightShort = s1.slice(12);
auto rightLong = s1.slice(12, 44);
auto leftLong = s1.slice(44, 76);
auto leftShort = s1.slice(76, 88);

auto leftLongRev = ReversePixelList{leftLong};
auto leftShortRev = ReversePixelList{leftShort};
auto leftSegmentTemp = PixelStitch{leftShortRev, leftLongRev};
auto rightSegmentTemp = PixelStitch{rightShort, rightLong};
auto leftSegment = PixelStitch{leftSegmentTemp, deadLongPixelList};
auto rightSegment = PixelStitch{rightSegmentTemp, deadLongPixelList};
auto wipeGroup = std::array<PixelList*, 2> { &leftSegment, &rightSegment };

class CorvetteMetalArtApplication : public UserApplication<> {
protected:
  auto configure(UserApplication::Configurer& app) -> void override {
    s1.setBrightness(.8f);
    app.addLEDs(s1);
    app.addSensor(irRemote);

    wipeEffect.shader = [](auto color, auto& params){
      if (params.pixelPosition <= params.wipeLength) {
        return Color::Sequential12(params.wipeCycle);
      }
      if (params.wipeCycle == 0) {
        return Color::OFF();
      }
      return Color::Sequential12(params.wipeCycle - 1);
    };
    wipeEffect.progression = EffectProgression::ConstantTime(Duration::Seconds(2));
    Effects::Start(wipeEffect, wipeGroup).detach();

    app.on<IRButtonPressed>([](auto& event) {
      switch (event.button) {
        case IRButtonType::BUTTON_LEFT:
          break;
        case IRButtonType::BUTTON_RIGHT:
          break;
        default:
          INFO("Unknown Button Pressed");
      }
    });
    app.useHeartbeatLED();
  }

  auto update() -> void override {
  }

  auto draw() -> void override {
  }
};


#endif //RGBLIB_CORVETTEMETALARTAPPLICATION_H
