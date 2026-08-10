//
// Created by Brandon on 2/1/26.
//

#include "Corvette.h"
#include "Vehicle.h"
#include "CorvetteApp.h"
#include "DeadPixelList.h"
#include "PixelStitch.h"
#include "Carousel.h"

using namespace rgb;

namespace {
auto deadPixelList = DeadPixelList{centerFiber.size()};
auto heartBeatCenterFiber = PixelStitch{centerFiber, deadPixelList};
auto heartBeatLeftFiber = PixelStitch{leftFiber, deadPixelList};
auto heartBeatRightFiber = PixelStitch{rightFiber, deadPixelList};
auto group = std::array<PixelList*, 3>({
  &heartBeatCenterFiber, &heartBeatLeftFiber, &heartBeatRightFiber
});

struct ColorPalette {
  Color idleFiberColor;
  Color idleFootColor;
  Color transitionFiberColor;
  Color transitionFootColor;
  Color lowRpmFiberColor;
  Color highRpmFiberColor;
  Color lowRpmFootColor;
  Color highRpmFootColor;

  auto lerp(const ColorPalette& to, float t) const -> ColorPalette {
    return {
      .idleFiberColor = idleFiberColor.lerpClamp(to.idleFiberColor, t),
      .idleFootColor = idleFootColor.lerpClamp(to.idleFootColor, t),
      .transitionFiberColor = transitionFiberColor.lerpClamp(to.transitionFiberColor, t),
      .transitionFootColor = transitionFootColor.lerpClamp(to.transitionFootColor, t),
      .lowRpmFiberColor = lowRpmFiberColor.lerpClamp(to.lowRpmFiberColor, t),
      .highRpmFiberColor = highRpmFiberColor.lerpClamp(to.highRpmFiberColor, t),
      .lowRpmFootColor = lowRpmFootColor.lerpClamp(to.lowRpmFootColor, t),
      .highRpmFootColor = highRpmFootColor.lerpClamp(to.highRpmFootColor, t),
    };
  }
};

template<size_t N>
class FadingCarousel {
public:
  static constexpr auto FADE_DURATION = Duration::Seconds(1);

  FadingCarousel(Carousel<ColorPalette, N> carousel)
    : mCarousel(std::move(carousel)), mPrevious(mCarousel.get()) {}

  auto get() -> ColorPalette {
    auto elapsed = Clock::Now().timeSince(mChangedAt);
    if constexpr (!FADE_DURATION.isZero()) {
      if (elapsed >= FADE_DURATION) {
        return mCarousel.get();
      }
    }
    auto t = static_cast<float>(elapsed.value) / static_cast<float>(FADE_DURATION.value);
    return mPrevious.lerp(mCarousel.get(), t);
  }

  auto next() -> void {
    recordPrevious();
    mCarousel.next();
  }

  auto prev() -> void {
    recordPrevious();
    mCarousel.prev();
  }

private:
  auto recordPrevious() -> void {
    mPrevious = get();
    mChangedAt = Clock::Now();
  }

  Carousel<ColorPalette, N> mCarousel;
  ColorPalette mPrevious;
  Timestamp mChangedAt{};
};

auto colorPalettes = FadingCarousel{Carousel{std::array{
  ColorPalette {
    .idleFiberColor = Color::RED(),
    .idleFootColor = Color::RED(),
    .transitionFiberColor = Color::BLUE(),
    .transitionFootColor = Color::BLUE(),
    .lowRpmFiberColor = Color::GREEN(), .highRpmFiberColor = Color::RED(),
    .lowRpmFootColor = FOOT_PURPLE, .highRpmFootColor = Color::RED(),
  },
  ColorPalette {
    .idleFiberColor = FIBER_PURPLE,
    .idleFootColor = FOOT_PURPLE,
    .transitionFiberColor = Color::RED(),
    .transitionFootColor = Color::RED(),
    .lowRpmFiberColor = Color::GREEN(), .highRpmFiberColor = Color::RED(),
    .lowRpmFootColor = Color::GREEN(), .highRpmFootColor = Color::RED(),
  },
  ColorPalette {
    .idleFiberColor = FIBER_PURPLE,
    .idleFootColor = Color::BLUE(),
    .transitionFiberColor = Color::RED(),
    .transitionFootColor = Color::RED(),
    .lowRpmFiberColor = Color::GREEN(), .highRpmFiberColor = Color::RED(),
    .lowRpmFootColor = FOOT_PURPLE, .highRpmFootColor = FOOT_PURPLE,
  },
  ColorPalette {
    .idleFiberColor = Color::RED(),
    .idleFootColor = Color::RED(),
    .transitionFiberColor = Color::GREEN(),
    .transitionFootColor = Color::GREEN(),
    .lowRpmFiberColor = Color::FromBytes(255, 0, 10), .highRpmFiberColor = Color::FromBytes(255, 0, 10),
    .lowRpmFootColor = Color::BLUE(), .highRpmFootColor = Color::FromBytes(255, 0, 10),
  },
}}};
}

ColdStartState Corvette::COLD_START_STATE{};
SleepState Corvette::SLEEP_STATE{};
DrivingState Corvette::DRIVING_STATE{};
IdleState Corvette::IDLE_STATE{};
RainbowState Corvette::RAINBOW_STATE{};

auto Corvette::setup() -> void {
  mState = &SLEEP_STATE;
  chasingEffect.buildup = true;
  chasingEffect.reversed = true;
  chasingEffect.delay = Duration::Milliseconds(50);
  chasingEffect.trailLength = Length::Ratio(.2f);
  chasingEffect.shader = [](auto color, auto& params) {
    return color * 2;
  };
}

auto Corvette::init() -> void {
  transitionToColdStart();
}

auto Corvette::update() -> void {
  auto& vehicle = Vehicle::Instance();

  mPreviousRpm = mRpm;
  mRpm = vehicle.rpm();
  mSmoothRpm = RunningAverage(mSmoothRpm, mRpm, RPM_SMOOTHING_FACTOR);

  mPreviousSpeed = mSpeed;
  mSpeed = vehicle.speed();
  mSmoothSpeed = RunningAverage(mSmoothSpeed, mSpeed, RPM_SMOOTHING_FACTOR);

  mCoolantTemp = vehicle.coolantTemp();

  mThrottle = vehicle.throttlePosition();
  mSmoothThrottle = RunningAverage(mSmoothThrottle, mThrottle, .1f);

  mState->update(*this);

  mLastUpdate = Clock::Now();
}

auto Corvette::draw() -> void {
  mState->draw(*this);
}

auto Corvette::rpm() const -> revs_per_minute {
  return mRpm;
}

auto Corvette::smoothRpm() const -> revs_per_minute {
  return mSmoothRpm;
}

auto Corvette::Instance() -> Corvette& {
  static Corvette instance;
  return instance;
}

auto Corvette::state() const -> CorvetteState& {
  return *mState;
}

auto Corvette::speed() const -> kph {
  return mSpeed;
}

auto Corvette::smoothSpeed() const -> kph {
  return mSmoothSpeed;
}

auto Corvette::throttlePosition() const -> percent {
  return mThrottle;
}


auto Corvette::smoothThrottlePosition() const -> percent {
  return mSmoothThrottle;
}


auto Corvette::setState(CorvetteState& state) -> CorvetteState* {
  auto previous = mState;
  mState = &state;
  return previous;
}

auto Corvette::transitionToIdle(Duration pulseDuration) -> void {
  ASSERT(mState != &IDLE_STATE, "Already in Idle Mode");
  TRACE("mState = IDLE");
  IDLE_STATE.reset(Clock::Now(), pulseDuration);
  auto previousState = setState(IDLE_STATE);
  CorvetteApp::PublishEvent(IdleModeEntered{{Clock::Now()}, previousState});
}

auto Corvette::transitionToDriving(bool chargeUp) -> void {
  ASSERT(mState != &IDLE_STATE, "Already in Driving Mode");
  TRACE("mState = MOVING");
  DRIVING_STATE.reset(Clock::Now(), chargeUp);
  auto previousState = setState(DRIVING_STATE);
  CorvetteApp::PublishEvent(DriveModeEntered{{Clock::Now()}, previousState});
}

auto Corvette::transitionToSleeping() -> void {
  ASSERT(mState != &SLEEP_STATE, "Already in Sleep Mode");
  TRACE("mState = SLEEP");
  SLEEP_STATE.reset(Clock::Now());
  auto previousState = setState(SLEEP_STATE);
  chaseHandle.stop();
  CorvetteApp::PublishEvent(SleepModeEntered{{Clock::Now()}, previousState});
}

auto Corvette::transitionToColdStart() -> void {
  ASSERT(mState == &SLEEP_STATE, "Can only enter Cold Start from sleeping");
  TRACE("mState = COLD_START");
  COLD_START_STATE.reset(Clock::Now());
  auto previousState = setState(COLD_START_STATE);
  chaseHandle = Effects::Start(chasingEffect, group);
  CorvetteApp::PublishEvent(ColdStartModeEntered{{Clock::Now()}, previousState});
}

auto Corvette::toggleHoldMode() -> void {
  if (mHoldMode) {
    mHoldMode = false;
    if (satisfiesIdleConditions()) {
      transitionToIdle(DEFAULT_PULSE_DURATION);
    }
  }
  else {
    mHoldMode = true;
    if (isStopped()) {
      transitionToDriving(true);
    }
  }
}

auto Corvette::toggleForceRainbowMode() -> void {
  if (mRainbowMode) {
    mRainbowMode = false;
    exitRainbowMode();
  }
  else {
    mRainbowMode = true;
    if (!inRainbowMode()) {
      enterRainbowMode();
    }
  }
}

auto Corvette::togglePulseMode() -> void {
  mPulseMode = !mPulseMode;
}

auto Corvette::nextColorPalette() -> void {
  colorPalettes.next();
}

auto Corvette::prevColorPalette() -> void {
  colorPalettes.prev();
}

auto Corvette::enterRainbowMode() -> void {
  ASSERT(mState != &RAINBOW_STATE, "Already in Rainbow Mode");
  TRACE("mState = RAINBOW");
  RAINBOW_STATE.reset(Clock::Now(), mThrottle);
  chaseHandle.stop();
  auto previousState = setState(RAINBOW_STATE);
  CorvetteApp::PublishEvent(RainbowModeEntered{{Clock::Now()}, previousState});
}

auto Corvette::exitRainbowMode() -> void {
  INFO("exitRainbowMode");
  chaseHandle = Effects::Start(chasingEffect, group);
  if (satisfiesIdleConditions()) {
    transitionToIdle(Duration::Seconds(2));
  }
  else {
    transitionToDriving(false);
  }
}

auto Corvette::satisfiesIdleConditions() const -> bool {
  return mRpm <= STARTING_RPM && mSpeed == 0 && !mHoldMode;
}

auto Corvette::satisfiesRainbowConditions() const -> bool {
  return mRpm >= RAINBOW_RPM || mRainbowMode;
}

auto Corvette::drawSleepEffects(normal phase) -> void {
  if (phase > 1.0f) {
    return;
  }

  auto palette = colorPalettes.get();
  auto colorFiber = palette.idleFiberColor.lerpClamp(palette.transitionFiberColor, phase);
  auto colorFoot = palette.idleFootColor.lerpClamp(palette.transitionFootColor, phase);
  auto fiberBrightness = GetFiberBrightness();

  leftFoot.fillRatio(colorFoot, 1.0f - phase);
  rightFoot.fillRatio(colorFoot, 1.0f - phase);
  centerFiber.fillRatioReverse(colorFiber * fiberBrightness, 1.0f - phase);
  leftFiber.fillRatioReverse(colorFiber * fiberBrightness, 1.0f - phase);
  rightFiber.fillRatioReverse(colorFiber * fiberBrightness, 1.0f - phase);
}

auto Corvette::drawIdleEffects(normal fillPercent, normal colorPercent, Duration pulseDuration) -> void {
  auto palette = colorPalettes.get();
  auto colorFiber = palette.transitionFiberColor.lerpClamp(palette.idleFiberColor, colorPercent);
  auto colorFoot = palette.transitionFootColor.lerpClamp(palette.idleFootColor, colorPercent);
  auto fiberBrightness = GetFiberBrightness();

  normal pulse;
  if (mPulseMode) {
    pulse = Pulse(Clock::Now(), pulseDuration);
  }
  else {
    pulse = 1.0f;
  }

  leftFoot.fillRatio(colorFoot * pulse, fillPercent);
  rightFoot.fillRatio(colorFoot * pulse, fillPercent);
  centerFiber.fillRatioReverse(colorFiber * fiberBrightness, fillPercent);
  leftFiber.fillRatioReverse(colorFiber * fiberBrightness, fillPercent);
  rightFiber.fillRatioReverse(colorFiber * fiberBrightness, fillPercent);
}

auto Corvette::drawRpmEffects(normal fillPercent) -> void {
  auto fiberRpmColorPercent = (static_cast<float>(mSmoothRpm) - RPM_LOW) / (RPM_HIGH - RPM_LOW);
  fiberRpmColorPercent = Clamp(fiberRpmColorPercent, 0.0f, 1.0f);
  if (fiberRpmColorPercent < 0.0f) {
    fiberRpmColorPercent = 0.0f;
  }

  // auto footLow = 3000;
  // auto footHigh = 3700;
  // auto footRpmColorPercent = (static_cast<float>(mSmoothRpm) - footLow) / (footHigh - footLow);
  // footRpmColorPercent = Clamp(footRpmColorPercent, 0.0f, 1.0f);
  // if (footRpmColorPercent < 0.0f) {
  //   footRpmColorPercent = 0.0f;
  // }


  auto palette = colorPalettes.get();

  auto rpmFootColor = palette.lowRpmFootColor.lerpClamp(palette.highRpmFootColor, fiberRpmColorPercent);
  auto rpmFiberColor = palette.lowRpmFiberColor.lerpClamp(palette.highRpmFiberColor, fiberRpmColorPercent);
  auto fiberBrightness = GetFiberBrightness();

  auto actualFootRpmColor = palette.lowRpmFootColor.lerpClamp(rpmFootColor, fillPercent);
  auto actualFiberRpmColor = palette.lowRpmFiberColor.lerpClamp(rpmFiberColor, fillPercent);

  leftFoot.fillRatio(actualFootRpmColor, fillPercent);
  rightFoot.fillRatio(actualFootRpmColor, fillPercent);

  centerFiber.fillRatioReverse(actualFiberRpmColor * fiberBrightness, fillPercent);
  leftFiber.fillRatioReverse(actualFiberRpmColor * fiberBrightness, fillPercent);
  rightFiber.fillRatioReverse(actualFiberRpmColor * fiberBrightness, fillPercent);
}

auto Corvette::drawRainbowEffects(normal fillPercent) -> void {
  auto now = Clock::Now();
  auto footLedCount = leftFoot.length();
  auto footRainbowLevel = std::min(static_cast<uint>(footLedCount * fillPercent), footLedCount);

  for (u16 index = 0; index < footLedCount && index < footRainbowLevel; ++index) {
    auto ratio = static_cast<float>(index) / static_cast<float>(footLedCount);
    auto offset = now.percentOf(Duration::Seconds(2));
    auto hue = ratio + offset;
    if (hue > 1.0f) {
      hue = hue - floorf(hue);
    }
    auto rainbowFootColor = Color::HslToRgb(hue);

    leftFoot.set(index, rainbowFootColor);
    rightFoot.set(index, rainbowFootColor);
  }

  auto fiberLedCount = centerFiber.length();
  auto fiberRainbowLevel = std::min(static_cast<uint>(fiberLedCount * fillPercent), fiberLedCount) + RAINBOW_WHITE_LENGTH;
  auto fiberBrightness = GetFiberBrightness() * 1.5f;

  for (int i = 0; i < fiberLedCount && i < fiberRainbowLevel; ++i) {
    if (i < fiberRainbowLevel - RAINBOW_WHITE_LENGTH) {
      auto ratio = static_cast<float>(fiberLedCount - i) / static_cast<float>(fiberLedCount);
      auto offset = now.percentOf(Duration::Seconds(2));
      auto hue = ratio + offset;
      if (hue > 1.0f) {
        hue = hue - floorf(hue);
      }
      auto rainbowFiberColor = Color::HslToRgb(1.0f - hue);
      centerFiber.set(fiberLedCount - 1 - i, rainbowFiberColor * fiberBrightness);
      leftFiber.set(fiberLedCount - 1 - i, rainbowFiberColor * fiberBrightness);
      rightFiber.set(fiberLedCount - 1 - i, rainbowFiberColor * fiberBrightness);
    }
    else {
      centerFiber.set(fiberLedCount - 1 - i, Color::WHITE() * fiberBrightness);
      leftFiber.set(fiberLedCount - 1 - i, Color::WHITE() * fiberBrightness);
      rightFiber.set(fiberLedCount - 1 - i, Color::WHITE() * fiberBrightness);
    }
  }

}

auto Corvette::coolantTemp() const -> fahrenheit {
  return mCoolantTemp;
}

auto Corvette::isConnected() const -> bool {
  return Vehicle::Instance().isConnected();
}

auto Corvette::inRainbowMode() const -> bool {
  return mState == &RAINBOW_STATE;
}

auto Corvette::inForcedRainbowMode() const -> bool {
  return mRainbowMode;
}

auto Corvette::isStopped() const -> bool {
  return mState == &IDLE_STATE || mState == &COLD_START_STATE;
}

auto Corvette::isSleeping() const -> bool {
  return mState == &SLEEP_STATE;
}

auto Corvette::GetFiberBrightness() -> float {
  return Brightness::GetBrightness({
      .dim = .1f,
      .medium = .3f,
      .bright = .5f,
      .max = 1.0f
    });
}
