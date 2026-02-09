//
// Created by Brandon on 2/4/26.
//

#include "LincolnTownCarState.h"
#include "LincolnTownCar.h"
#include "Application.h"
#include "Clock.h"

using namespace rgb;

auto ColdStartState::update(LincolnTownCar& vehicle) -> void {
  LincolnTownCar::STOPPED_STATE.update(vehicle);
}

auto StoppedState::reset(LincolnTownCar& vehicle) -> void {

}

auto StoppedState::update(LincolnTownCar& vehicle) -> void {
  if (vehicle.mRpm > LincolnTownCar::STARTING_RPM) {
    vehicle.transitionToMoving();
  }
}

auto MovingState::reset(LincolnTownCar& vehicle) -> void {

}

auto MovingState::update(LincolnTownCar& vehicle) -> void {
  if (vehicle.mRpm >= LincolnTownCar::RAINBOW_RPM) {
    vehicle.enterOrExtendRainbowMode();
  }
  else if (vehicle.mRainbowMode && Clock::Now() >= vehicle.mRainbowMode.value() + LincolnTownCar::RAINBOW_DURATION) {
    vehicle.exitRainbowMode();
  }

  if (vehicle.mRpm <= LincolnTownCar::STARTING_RPM && vehicle.mSpeed == 0) {
    vehicle.transitionToStopped();
  }
}