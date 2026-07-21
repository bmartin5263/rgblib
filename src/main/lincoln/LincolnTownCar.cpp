//
// Created by Brandon on 2/1/26.
//

#include "LincolnTownCar.h"
#include "Vehicle.h"
#include "LincolnAppEvents.h"

using namespace rgb;

LincolnColdStartState LincolnTownCar::COLD_START_STATE{};
LincolnMovingState LincolnTownCar::MOVING_STATE{};
LincolnStoppedState LincolnTownCar::STOPPED_STATE{};

auto LincolnTownCar::update() -> void {
  auto& vehicle = Vehicle::Instance();

  mPreviousRpm = mRpm;
  mRpm = vehicle.rpm();
  RunningAverage(mSmoothRpm, mRpm, RPM_SMOOTHING_FACTOR);

  mPreviousSpeed = mSpeed;
  mSpeed = vehicle.speed();
  RunningAverage(mSmoothSpeed, mSpeed, RPM_SMOOTHING_FACTOR);

  mCoolantTemp = vehicle.coolantTemp();

  mThrottle = vehicle.throttlePosition();
  RunningAverage(mSmoothThrottle, mThrottle, .1f);

  INFO("pre-update, mState == COLD_START: %i", mState == &COLD_START_STATE);
  mState->update(*this);

  mLastUpdate = Clock::Now();
}

auto LincolnTownCar::rpm() const -> revs_per_minute {
  return mRpm;
}

auto LincolnTownCar::smoothRpm() const -> revs_per_minute {
  return mSmoothRpm;
}

auto LincolnTownCar::Instance() -> LincolnTownCar& {
  static LincolnTownCar instance;
  return instance;
}

auto LincolnTownCar::state() const -> LincolnTownCarState& {
  return *mState;
}


auto LincolnTownCar::startedMovingAt() const -> rgb::Timestamp {
  return mMovingAt;
}

auto LincolnTownCar::speed() const -> rgb::kph {
  return mSpeed;
}


auto LincolnTownCar::smoothSpeed() const -> rgb::kph {
  return mSmoothSpeed;
}


auto LincolnTownCar::throttlePosition() const -> rgb::percent {
  return mThrottle;
}


auto LincolnTownCar::smoothThrottlePosition() const -> rgb::percent {
  return mSmoothThrottle;
}


auto LincolnTownCar::transitionToStopped() -> void {
  INFO("mState = STOPPED");
  mRainbowMode.reset();
  LincolnApp::PublishEvent(CarStopped{{Clock::Now()}});
  mState = &STOPPED_STATE;
  mStoppedAt = Clock::Now();
}

auto LincolnTownCar::transitionToMoving() -> void {
  INFO("mState = MOVING");
  LincolnApp::PublishEvent(CarMoving{{Clock::Now()}});
  mState = &MOVING_STATE;
  mStoppedAt = Clock::Now();
}

auto LincolnTownCar::enterOrExtendRainbowMode() -> void {
  if (mRainbowMode) {
    mRainbowMode = Clock::Now();
    // early exit to avoid event
    return;
  }
  mRainbowMode = Clock::Now();
  mThrottleWhenRainbowStart = mThrottle;
  LincolnApp::PublishEvent(RainbowModeEntered{{Clock::Now()}});
}

auto LincolnTownCar::exitRainbowMode() -> void {
  if (!mRainbowMode) {
    return;
  }
  mRainbowMode = std::nullopt;
  LincolnApp::PublishEvent(RainbowModeExited{{Clock::Now()}});
}

auto LincolnTownCar::coolantTemp() const -> rgb::fahrenheit {
  return mCoolantTemp;
}

auto LincolnTownCar::isConnected() const -> bool {
  return Vehicle::Instance().isConnected();
}

auto LincolnTownCar::inRainbowMode() const -> bool {
  return mRainbowMode.has_value();
}

auto LincolnTownCar::isStopped() const -> bool {
  return mState == &STOPPED_STATE || mState == &COLD_START_STATE;
}
