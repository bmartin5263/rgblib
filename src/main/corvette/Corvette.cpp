//
// Created by Brandon on 2/1/26.
//

#include "Corvette.h"
#include "Vehicle.h"
#include "CorvetteApp.h"
#include "DeadPixelList.h"
#include "PixelStitch.h"

using namespace rgb;

namespace {
constexpr auto NINTY_MPH = 144.f;
auto deadPixelList = DeadPixelList{centerFiber.size()};
auto heartBeatCenterFiber = PixelStitch{centerFiber, deadPixelList};
auto heartBeatLeftFiber = PixelStitch{leftFiber, deadPixelList};
auto heartBeatRightFiber = PixelStitch{rightFiber, deadPixelList};
auto group = std::array<PixelList*, 3>({
  &heartBeatCenterFiber, &heartBeatLeftFiber, &heartBeatRightFiber
});
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

  auto speed = static_cast<float>(mSmoothSpeed);
  auto chaseTime = Duration::Microseconds(LerpClamp(20000, 4000, speed / NINTY_MPH));
  chasingEffect.delay = chaseTime;

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

auto Corvette::transitionToIdle() -> void {
  ASSERT(mState != &IDLE_STATE, "Already in Idle Mode");
  TRACE("mState = IDLE");
  IDLE_STATE.reset(Clock::Now());
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
  if (mRpm <= STARTING_RPM && mSpeed == 0) {
    transitionToIdle();
  }
  else {
    transitionToDriving(false);
  }
}

auto Corvette::drawSleepEffects(normal phase) -> void {
  if (phase > 1.0f) {
    return;
  }

  auto colorFiber = FIBER_PURPLE.lerpClamp(Color::RED(), phase);
  auto colorFoot = FOOT_PURPLE.lerpClamp(Color::RED(), phase);
  auto fiberBrightness = GetFiberBrightness();

  leftFoot.fillRatio(colorFoot, 1.0f - phase);
  rightFoot.fillRatio(colorFoot, 1.0f - phase);
  centerFiber.fillRatioReverse(colorFiber * fiberBrightness, 1.0f - phase);
  leftFiber.fillRatioReverse(colorFiber * fiberBrightness, 1.0f - phase);
  rightFiber.fillRatioReverse(colorFiber * fiberBrightness, 1.0f - phase);
}

auto Corvette::drawIdleEffects(normal fillPercent, normal colorPercent) -> void {
  auto colorFiber = Color::RED().lerpClamp(FIBER_PURPLE, colorPercent);
  auto colorFoot = Color::RED().lerpClamp(FOOT_PURPLE, colorPercent);
  auto fiberBrightness = GetFiberBrightness();

  leftFoot.fillRatio(colorFoot, fillPercent);
  rightFoot.fillRatio(colorFoot, fillPercent);
  centerFiber.fillRatioReverse(colorFiber * fiberBrightness, fillPercent);
  leftFiber.fillRatioReverse(colorFiber * fiberBrightness, fillPercent);
  rightFiber.fillRatioReverse(colorFiber * fiberBrightness, fillPercent);
}

auto Corvette::drawRpmEffects(normal fillPercent) -> void {
  auto rpmColorPercent = (static_cast<float>(mSmoothRpm) - RPM_LOW) / (RPM_HIGH - RPM_LOW);
  rpmColorPercent = Clamp(rpmColorPercent, 0.0f, 1.0f);
  if (rpmColorPercent < 0.0f) {
    rpmColorPercent = 0.0f;
  }
  auto rpmColor = LOW_RPM_COLOR.lerpClamp(HIGH_RPM_COLOR, rpmColorPercent);
  auto actualRpmColor = Color::GREEN().lerpClamp(rpmColor, fillPercent);
  auto fiberBrightness = GetFiberBrightness();

  leftFoot.fillRatio(actualRpmColor, fillPercent);
  rightFoot.fillRatio(actualRpmColor, fillPercent);
  centerFiber.fillRatioReverse(actualRpmColor * fiberBrightness, fillPercent);
  leftFiber.fillRatioReverse(actualRpmColor * fiberBrightness, fillPercent);
  rightFiber.fillRatioReverse(actualRpmColor * fiberBrightness, fillPercent);
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
      auto offset = now.percentOf(Duration::Seconds(1));
      auto hue = ratio + offset;
      if (hue > 1.0f) {
        hue = hue - floorf(hue);
      }
      auto rainbowDashColor = Color::HslToRgb(1.0f - hue);
      centerFiber.set(fiberLedCount - 1 - i, rainbowDashColor * fiberBrightness);
      leftFiber.set(fiberLedCount - 1 - i, rainbowDashColor * fiberBrightness);
      rightFiber.set(fiberLedCount - 1 - i, rainbowDashColor * fiberBrightness);
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
