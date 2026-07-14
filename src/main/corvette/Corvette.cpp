//
// Created by Brandon on 2/1/26.
//

#include "Corvette.h"
#include "Vehicle.h"
#include "CorvetteApp.h"

using namespace rgb;

ColdStartState Corvette::COLD_START_STATE{};
DrivingState Corvette::DRIVING_STATE{};
IdleState Corvette::IDLE_STATE{};
RainbowState Corvette::RAINBOW_STATE{};

auto Corvette::init() -> void {
  COLD_START_STATE.reset(Clock::Now());
  mState = &COLD_START_STATE;
}

auto Corvette::update() -> void {
  static bool initialized = false;
  if (!initialized) {
    // Wait as long as to set the "enteredAt" since the effect depends on it
    COLD_START_STATE.reset(Clock::Now());
    initialized = true;
  }

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

auto Corvette::enterRainbowMode() -> void {
  ASSERT(mState != &RAINBOW_STATE, "Already in Rainbow Mode");
  TRACE("mState = RAINBOW");
  RAINBOW_STATE.reset(Clock::Now(), mThrottle);
  auto previousState = setState(RAINBOW_STATE);
  CorvetteApp::PublishEvent(RainbowModeEntered{{Clock::Now()}, previousState});
}

auto Corvette::exitRainbowMode() -> void {
  INFO("exitRainbowMode");
  if (mRpm <= STARTING_RPM && mSpeed == 0) {
    transitionToIdle();
  }
  else {
    transitionToDriving(false);
  }
}

auto Corvette::drawIdleEffects(normal fillPercent, normal colorPercent) -> void {
  auto colorFiber = Color::RED().lerpClamp(FIBER_PURPLE, colorPercent);
  auto colorFoot = Color::RED().lerpClamp(FOOT_PURPLE, colorPercent);

  leftFoot.fillRatio(colorFoot, fillPercent);
  rightFoot.fillRatio(colorFoot, fillPercent);
  centerFiber.fillRatioReverse(colorFiber * .3f, fillPercent);
}

auto Corvette::drawRpmEffects(normal fillPercent) -> void {
  auto rpmColorPercent = (static_cast<float>(mSmoothRpm) - RPM_LOW) / (RPM_HIGH - RPM_LOW);
  if (rpmColorPercent < 0.0f) {
    rpmColorPercent = 0.0f;
  }
  auto rpmColor = LOW_RPM_COLOR.lerpClamp(HIGH_RPM_COLOR, rpmColorPercent);

  auto rpmFillPercent = (mSmoothRpm - 500) / 3500.f;
  if (rpmFillPercent < 0.0f) {
    rpmFillPercent = 0.0f;
  }

  leftFoot.fillRatio(rpmColor, fillPercent);
  rightFoot.fillRatio(rpmColor, fillPercent);
  centerFiber.fillRatioReverse(rpmColor * .1f, fillPercent);
  centerFiber.fillRatioReverse(rpmColor * .3f, std::min(fillPercent, rpmFillPercent));
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

  for (int i = 0; i < fiberLedCount && i < fiberRainbowLevel; ++i) {
    if (i < fiberRainbowLevel - RAINBOW_WHITE_LENGTH) {
      auto ratio = static_cast<float>(fiberLedCount - i) / static_cast<float>(fiberLedCount);
      auto offset = now.percentOf(Duration::Seconds(1));
      auto hue = ratio + offset;
      if (hue > 1.0f) {
        hue = hue - floorf(hue);
      }
      auto rainbowDashColor = Color::HslToRgb(1.0f - hue);
      centerFiber.set(fiberLedCount - 1 - i, rainbowDashColor * .5f);
    }
    else {
      centerFiber.set(fiberLedCount - 1 - i, Color::WHITE() * .5f);
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
