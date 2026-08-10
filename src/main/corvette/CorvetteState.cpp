//
// Created by Brandon on 2/4/26.
//

#include "CorvetteState.h"
#include "Corvette.h"
#include "Clock.h"

using namespace rgb;

auto ColdStartState::reset(Timestamp enteredAt) -> void {
  this->enteredAt = enteredAt;
}

auto ColdStartState::update(Corvette& vehicle) -> void {
  auto chaseTime = Duration::Microseconds(20000);
  vehicle.chasingEffect.delay = chaseTime;

  if (vehicle.mRpm > Corvette::STARTING_RPM
    && (Clock::Now().timeSince(enteredAt) > Duration::Seconds(5) || vehicle.mSpeed > 0)) {
    vehicle.transitionToDriving(true);
  }
}

auto IdleState::reset(Timestamp enteredAt, Duration pulseDuration) -> void {
  this->enteredAt = enteredAt;
  this->pulseDuration = pulseDuration;
}

auto IdleState::update(Corvette& vehicle) -> void {
  auto chaseTime = Duration::Microseconds(20000);
  vehicle.chasingEffect.delay = chaseTime;

  auto now = Clock::Now() - enteredAt;
  auto percentComplete = now.percentOf(Duration::Seconds(1));
  if (vehicle.mRpm > Corvette::STARTING_RPM && percentComplete >= 1.0f) {
    vehicle.transitionToDriving(true);
  }
}

auto DrivingState::reset(Timestamp enteredAt, bool chargeUp) -> void {
  this->enteredAt = enteredAt;
  this->chargeUp = chargeUp;
  this->maxSpeed = 0;
}

auto DrivingState::update(Corvette& vehicle) -> void {
  auto speed = vehicle.mSpeed;
  if (speed > maxSpeed) {
    maxSpeed = speed;
  }

  auto smoothSpeed = static_cast<float>(vehicle.mSmoothSpeed);
  auto chaseTime = Duration::Microseconds(LerpClamp(12000, 3000, smoothSpeed / MphToKph(100)));
  vehicle.chasingEffect.delay = chaseTime;

  if (vehicle.satisfiesRainbowConditions()) {
    vehicle.enterRainbowMode();
  }
  else if (vehicle.satisfiesIdleConditions()) {
    auto pulseDuration = Corvette::DEFAULT_PULSE_DURATION;
    if (maxSpeed > MphToKph(90)) {
      pulseDuration = Duration::Seconds(2);
    }
    else if (maxSpeed > MphToKph(70)) {
      pulseDuration = Duration::Seconds(3);
    }
    else if (maxSpeed > MphToKph(50)) {
      pulseDuration = Duration::Seconds(4);
    }
    vehicle.transitionToIdle(pulseDuration);
  }
}

auto RainbowState::reset(Timestamp enteredAt, percent throttleWhenRainbowStart) -> void {
  this->enteredAt = enteredAt;
  this->effectiveStartTime = enteredAt;
  this->throttleWhenRainbowStart = throttleWhenRainbowStart;
}

auto RainbowState::update(Corvette& vehicle) -> void {
  auto endTime = effectiveStartTime + Corvette::RAINBOW_DURATION;
  if (
    Clock::Now() >= endTime
    && (throttleWhenRainbowStart < .1f || throttleWhenRainbowStart - vehicle.mThrottle > .1f)
    && !vehicle.mRainbowMode
  ) {
    vehicle.exitRainbowMode();
  }
  else if (vehicle.satisfiesRainbowConditions()) {
    effectiveStartTime = Clock::Now();
  }
}

void ColdStartState::draw(Corvette& vehicle) {
  auto now = Clock::Now() - enteredAt;
  auto percentComplete = now.percentOf(Duration::Seconds(1));
  vehicle.drawIdleEffects(percentComplete, percentComplete);
}

void IdleState::draw(Corvette& vehicle) {
  auto now = Clock::Now() - enteredAt;
  auto percentComplete = now.percentOf(Duration::Seconds(1));
  vehicle.drawRpmEffects();
  vehicle.drawIdleEffects(percentComplete, percentComplete);
}

void DrivingState::draw(Corvette& vehicle) {
  auto now = Clock::Now() - enteredAt;
  auto percentComplete = chargeUp ? now.percentOf(Duration::Seconds(1)) : 1.0f;
  vehicle.drawIdleEffects(1.0f, 1.0f - percentComplete);
  vehicle.drawRpmEffects(percentComplete);
}

void RainbowState::draw(Corvette& vehicle) {
  auto now = Clock::Now() - enteredAt;
  auto percentComplete = now.percentOf(Duration::Milliseconds(500));
  vehicle.drawRpmEffects();
  vehicle.drawRainbowEffects(percentComplete);
}

auto SleepState::reset(Timestamp enteredAt) -> void {
  this->enteredAt = enteredAt;
}

auto SleepState::update(Corvette& vehicle) -> void {
  // delay(1000);
  auto now = Clock::Now() - enteredAt;
  auto percentComplete = now.percentOf(Duration::Seconds(5));
  if (percentComplete > 1.0f) {
    delay(1000);
  }
}

void SleepState::draw(Corvette& vehicle) {
  auto now = Clock::Now() - enteredAt;
  auto percentComplete = now.percentOf(Duration::Seconds(1));
  vehicle.drawSleepEffects(percentComplete);
}
