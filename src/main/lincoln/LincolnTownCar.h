//
// Created by Brandon on 2/1/26.
//

#ifndef RGBLIB_LINCOLNTOWNCAR_H
#define RGBLIB_LINCOLNTOWNCAR_H

#include "Vehicle.h"
#include "Flag.h"
#include "LincolnTownCarState.h"

//enum LincolnTownCarState {
//  COLD_START,
//  STOPPED,
//  MOVING,
//  HIGHWAY
//};

class LincolnTownCar {
  static ColdStartState COLD_START_STATE;
  static StoppedState STOPPED_STATE;
  static MovingState MOVING_STATE;
public:
  friend class StoppedState;
  friend class ColdStartState;
  friend class MovingState;

  static constexpr auto RPM_SMOOTHING_FACTOR = 0.03f;
  static constexpr auto MAX_IDLE_RPM = 750;
  static constexpr auto STARTING_RPM = 1000;
  static constexpr auto RAINBOW_RPM = 3000;
  static constexpr auto RAINBOW_DURATION = rgb::Duration::Seconds(5);

  auto update() -> void;

  auto coolantTemp() const -> rgb::fahrenheit;
  auto rpm() const -> rgb::revs_per_minute;
  auto smoothRpm() const -> rgb::revs_per_minute;
  auto speed() const -> rgb::kph;
  auto smoothSpeed() const -> rgb::kph;
  auto state() const -> LincolnTownCarState&;
  auto startedMovingAt() const -> rgb::Timestamp;
  auto isConnected() const -> bool;
  auto inRainbowMode() const -> bool;

  static auto Instance() -> LincolnTownCar&;

  LincolnTownCar() = default;
  LincolnTownCar(const LincolnTownCar& rhs) = delete;
  LincolnTownCar(LincolnTownCar&& rhs) noexcept = delete;
  LincolnTownCar& operator=(const LincolnTownCar& rhs) = delete;
  LincolnTownCar& operator=(LincolnTownCar&& rhs) noexcept = delete;
  ~LincolnTownCar() = default;

private:
  auto transitionToStopped() -> void;
  auto transitionToMoving() -> void;

  auto enterOrExtendRainbowMode() -> void;
  auto exitRainbowMode() -> void;

  rgb::Timestamp mLastUpdate{rgb::Timestamp::Zero()};
  rgb::Timestamp mMovingAt{rgb::Timestamp::Zero()};
  rgb::Timestamp mStoppedAt{rgb::Timestamp::Zero()};
  rgb::flag mRainbowMode{};
  rgb::kph mPreviousSpeed{};
  rgb::kph mSpeed{};
  rgb::kph mSmoothSpeed{};
  rgb::revs_per_minute mPreviousRpm{};
  rgb::revs_per_minute mRpm{};
  rgb::revs_per_minute mSmoothRpm{};
  rgb::fahrenheit mCoolantTemp{};
  LincolnTownCarState* mState{&COLD_START_STATE};
};

#endif //RGBLIB_LINCOLNTOWNCAR_H
