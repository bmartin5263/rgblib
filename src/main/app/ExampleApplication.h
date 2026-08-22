//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_EXAMPLEAPPLICATION_H
#define RGBLIB_EXAMPLEAPPLICATION_H

#include "UserApplication.h"
#include "LEDStrip.h"
#include "ReversePixelList.h"
#include "PixelSlice.h"
#include "ChaseEffect.h"

using namespace rgb;

// Set up the LED Strip and Sensors
inline auto ledCircuit = LEDStrip<38, D4_RGB>();

// Effects
inline auto chaseEffect = ChaseEffect{};     // A chase effect template, can be applied to multiple segments simultaneously
inline auto effectHandle = EffectHandle{};   // Resource handle to control the running effect, not strictly needed

// 2 Segments carved out from the primary strip
inline auto leftSide = ledCircuit.slice(16);
inline auto rightSide = ledCircuit.slice(16, 38);
inline auto leftSideReversed = ReversePixelList{leftSide};
inline auto chaseGroup = std::array<PixelList*, 2> { &leftSideReversed, &rightSide };

struct MyCustomEvent : BaseEvent {};
using MyAppEvents = Event<MyCustomEvent>;

class ExampleApplication : public UserApplication<MyAppEvents> {
protected:
  auto configure(Configurer& app) -> void override {
    app.addPixels(ledCircuit);   // Register the circuit to the app

    // Defines what color the wipe effect should apply to each pixel
    chaseEffect.shader = [](auto currentColor, auto& params){
      return Color::GREEN() * params.positionRatio;
    };
    // 1 seconds for a full cycle
    chaseEffect.progression = EffectProgression::ConstantTime(Duration::Seconds(1));

    // Start the effect on the group
    effectHandle = Effects::Start(chaseEffect, chaseGroup);
  }

  auto initialize() -> void override {
    Timer::SetTimeout(Duration::Seconds(60), [](){
      effectHandle.stop(); // cancel the effect acter a minute
    }).detach();
  }
};


#endif //RGBLIB_EXAMPLEAPPLICATION_H
