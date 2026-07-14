//
// Created by Brandon on 2/4/26.
//

#include "CorvetteState.h"
#include "Corvette.h"
#include "CorvetteApp.h"
#include "Application.h"
#include "Clock.h"

using namespace rgb;

auto ColdStartState::reset(Timestamp enteredAt) -> void {
  this->enteredAt = enteredAt;
}

auto ColdStartState::update(Corvette& vehicle) -> void {
  Corvette::IDLE_STATE.update(vehicle);
}

auto IdleState::reset(Timestamp enteredAt) -> void {
  this->enteredAt = enteredAt;
}

auto IdleState::update(Corvette& vehicle) -> void {
  if (vehicle.mRpm > Corvette::STARTING_RPM) {
    vehicle.transitionToDriving(true);
  }
}

auto DrivingState::reset(Timestamp enteredAt, bool chargeUp) -> void {
  this->enteredAt = enteredAt;
  this->chargeUp = chargeUp;
}

auto DrivingState::update(Corvette& vehicle) -> void {
  if (vehicle.mRpm >= Corvette::RAINBOW_RPM) {
    vehicle.enterRainbowMode();
  }
  else if (vehicle.mRpm <= Corvette::STARTING_RPM && vehicle.mSpeed == 0) {
    vehicle.transitionToIdle();
  }
}

auto RainbowState::reset(Timestamp enteredAt, percent throttleWhenRainbowStart) -> void {
  this->enteredAt = enteredAt;
  this->effectiveStartTime = enteredAt;
  this->throttleWhenRainbowStart = throttleWhenRainbowStart;
}

auto RainbowState::update(Corvette& vehicle) -> void {
  auto endTime = effectiveStartTime + Corvette::RAINBOW_DURATION;
  if (Clock::Now() >= endTime && (throttleWhenRainbowStart < .1f || throttleWhenRainbowStart - vehicle.mThrottle > .1f)) {
    vehicle.exitRainbowMode();
  }
  else if (vehicle.mRpm >= Corvette::RAINBOW_RPM) {
    effectiveStartTime = Clock::Now();
  }
}

void ColdStartState::draw(Corvette& vehicle) {
  auto current = Clock::Now() - enteredAt;
  auto percentComplete = current.percentOf(Duration::Seconds(1));
  vehicle.drawIdleEffects(percentComplete, percentComplete);
}

void IdleState::draw(Corvette& vehicle) {
  auto current = Clock::Now() - enteredAt;
  auto percentComplete = current.percentOf(Duration::Seconds(1));
  vehicle.drawRpmEffects();
  vehicle.drawIdleEffects(percentComplete, percentComplete);
}

void DrivingState::draw(Corvette& vehicle) {
  auto current = Clock::Now() - enteredAt;
  auto percentComplete = chargeUp ? current.percentOf(Duration::Seconds(1)) : 1.0f;
  vehicle.drawIdleEffects(1.0f, 1.0f - percentComplete);
  vehicle.drawRpmEffects(percentComplete);
}

void RainbowState::draw(Corvette& vehicle) {
  auto current = Clock::Now() - enteredAt;
  auto percentComplete = current.percentOf(Duration::Milliseconds(500));
  vehicle.drawRpmEffects();
  vehicle.drawRainbowEffects(percentComplete);
}

