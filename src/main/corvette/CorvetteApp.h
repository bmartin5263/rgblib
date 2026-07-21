//
// Created by Brandon on 7/13/26.
//

#ifndef RGBLIB_CORVETTEAPP_H
#define RGBLIB_CORVETTEAPP_H

#include "EventType.h"
#include "UserApplication.h"
#include "FastLEDStrip.h"
#include "Types.h"
#include "CorvetteState.h"

#ifndef RGB_CORVETTE_LEFT_PIN
#define RGB_CORVETTE_LEFT_PIN rgb::D2_RGB
#endif
#ifndef RGB_CORVETTE_RIGHT_PIN
#define RGB_CORVETTE_RIGHT_PIN rgb::D3_RGB
#endif
#ifndef RGB_CORVETTE_TACHOMETER_PIN
#define RGB_CORVETTE_TACHOMETER_PIN rgb::D4_RGB
#endif
#ifndef RGB_CORVETTE_CENTER_FIBER_PIN
#define RGB_CORVETTE_CENTER_FIBER_PIN rgb::D5_RGB
#endif
#ifndef RGB_CORVETTE_LEFT_FIBER_PIN
#define RGB_CORVETTE_LEFT_FIBER_PIN rgb::D6_RGB
#endif
#ifndef RGB_CORVETTE_RIGHT_FIBER_PIN
#define RGB_CORVETTE_RIGHT_FIBER_PIN rgb::D7_RGB
#endif

struct DriveModeEntered : rgb::BaseEvent {
  CorvetteState* previousState;
};
struct IdleModeEntered : rgb::BaseEvent {
  CorvetteState* previousState;
};
struct RainbowModeEntered : rgb::BaseEvent {
  CorvetteState* previousState;
};
struct SleepModeEntered : rgb::BaseEvent {
  CorvetteState* previousState;
};
struct ColdStartModeEntered : rgb::BaseEvent {
  CorvetteState* previousState;
};

using CorvetteAppEvents = rgb::Event<
  RainbowModeEntered,
  DriveModeEntered,
  IdleModeEntered,
  SleepModeEntered,
  ColdStartModeEntered
>;

using CorvetteApp = rgb::UserApplication<CorvetteAppEvents>;

static constexpr rgb::u16 FOOT_STRIP_LED_COUNT = 40;
static constexpr rgb::u16 FIBER_LED_COUNT = 70;
static constexpr rgb::u16 TACHOMETER_LED_COUNT = 16;
static constexpr rgb::u16 HALF_FOOT_STRIP_LED_COUNT = FOOT_STRIP_LED_COUNT / 2;
static constexpr rgb::u16 RAINBOW_WHITE_LENGTH = 3;

// Colors
static constexpr auto FOOT_PURPLE = rgb::Color {0.2f, 0.f, 1.0f};
static constexpr auto FIBER_PURPLE = rgb::Color {0.3f, 0.f, 1.0f};

// LEDs
using LeftFootStrip = rgb::FastLEDStrip<FOOT_STRIP_LED_COUNT, RGB_CORVETTE_LEFT_PIN>;
using RightFootStrip = rgb::FastLEDStrip<FOOT_STRIP_LED_COUNT, RGB_CORVETTE_RIGHT_PIN>;
using TachometerStrip = rgb::FastLEDStrip<TACHOMETER_LED_COUNT, RGB_CORVETTE_TACHOMETER_PIN, rgb::RgbwSupport::ENABLE>;
using CenterFiberStrip = rgb::FastLEDStrip<FIBER_LED_COUNT, RGB_CORVETTE_CENTER_FIBER_PIN>;
using LeftFiberStrip = rgb::FastLEDStrip<FIBER_LED_COUNT, RGB_CORVETTE_LEFT_FIBER_PIN>;
using RightFiberStrip = rgb::FastLEDStrip<FIBER_LED_COUNT, RGB_CORVETTE_RIGHT_FIBER_PIN>;

extern LeftFootStrip leftFoot;
extern RightFootStrip rightFoot;
extern TachometerStrip tachometer;
extern CenterFiberStrip centerFiber;
extern LeftFiberStrip leftFiber;
extern RightFiberStrip rightFiber;

#endif //RGBLIB_CORVETTEAPP_H
