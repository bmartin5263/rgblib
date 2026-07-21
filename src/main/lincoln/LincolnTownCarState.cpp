//
// Created by Brandon on 2/4/26.
//

#include "LincolnTownCarState.h"
#include "LincolnTownCar.h"
#include "Clock.h"

using namespace rgb;

auto LincolnColdStartState::update(LincolnTownCar& vehicle) -> void {
  INFO("Cold Start");
  LincolnTownCar::STOPPED_STATE.update(vehicle);
}

auto LincolnStoppedState::update(LincolnTownCar& vehicle) -> void {
  INFO("Stopped");
  if (vehicle.mRpm > LincolnTownCar::STARTING_RPM) {
    vehicle.transitionToMoving();
  }
}

auto LincolnMovingState::update(LincolnTownCar& vehicle) -> void {
  INFO("Moving");
  if (vehicle.mRpm >= LincolnTownCar::RAINBOW_RPM) {
    vehicle.enterOrExtendRainbowMode();
  }
  else if (
    vehicle.mRainbowMode
    && Clock::Now() >= vehicle.mRainbowMode.value() + LincolnTownCar::RAINBOW_DURATION
    && (vehicle.mThrottleWhenRainbowStart < .1f || vehicle.mThrottleWhenRainbowStart - vehicle.mThrottle > .1f)
  ) {
    vehicle.exitRainbowMode();
  }

  if (vehicle.mRpm <= LincolnTownCar::STARTING_RPM && vehicle.mSpeed == 0) {
    vehicle.transitionToStopped();
  }
}