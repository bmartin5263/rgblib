//
// Created by Brandon on 2/1/26.
//

#ifndef RGBLIB_CORVETTE_H
#define RGBLIB_CORVETTE_H

#include "ChasingEffectSpeedOnly.h"
#include "Flag.h"
#include "CorvetteState.h"
#include "RgbColor.h"

class Corvette {
  static ColdStartState COLD_START_STATE;
  static IdleState IDLE_STATE;
  static DrivingState DRIVING_STATE;
  static RainbowState RAINBOW_STATE;
  static SleepState SLEEP_STATE;
public:
  friend class IdleState;
  friend class ColdStartState;
  friend class DrivingState;
  friend class RainbowState;
  friend class SleepState;

  static constexpr auto RPM_SMOOTHING_FACTOR = 0.03f;
  static constexpr auto MAX_IDLE_RPM = 750;
  static constexpr auto STARTING_RPM = 1000;
  static constexpr auto RAINBOW_RPM = 4200;
  static constexpr auto RAINBOW_DURATION = rgb::Duration::Seconds(5);
  static constexpr auto LOW_RPM_COLOR = rgb::Color::GREEN();
  static constexpr auto HIGH_RPM_COLOR = rgb::Color::RED();
  static constexpr auto RPM_LOW = 1500;
  static constexpr auto RPM_HIGH = 3000;

  auto setup() -> void;
  auto init() -> void;
  auto update() -> void;
  auto draw() -> void;

  auto coolantTemp() const -> rgb::fahrenheit;
  auto rpm() const -> rgb::revs_per_minute;
  auto smoothRpm() const -> rgb::revs_per_minute;
  auto speed() const -> rgb::kph;
  auto smoothSpeed() const -> rgb::kph;
  auto throttlePosition() const -> rgb::percent;
  auto smoothThrottlePosition() const -> rgb::percent;
  auto state() const -> CorvetteState&;
  auto isConnected() const -> bool;
  auto inRainbowMode() const -> bool;
  auto isStopped() const -> bool;
  auto isSleeping() const -> bool;

  auto transitionToIdle() -> void;
  auto transitionToDriving(bool chargeUp) -> void;
  auto transitionToSleeping() -> void;
  auto transitionToColdStart() -> void;

  static auto Instance() -> Corvette&;

  Corvette() = default;
  Corvette(const Corvette& rhs) = delete;
  Corvette(Corvette&& rhs) noexcept = delete;
  Corvette& operator=(const Corvette& rhs) = delete;
  Corvette& operator=(Corvette&& rhs) noexcept = delete;
  ~Corvette() = default;

private:
  auto setState(CorvetteState& state) -> CorvetteState*;
  auto enterRainbowMode() -> void;
  auto exitRainbowMode() -> void;

  auto drawIdleEffects(rgb::normal fillPercent = 1.0f, rgb::normal colorPercent = 1.0f) -> void;
  auto drawRpmEffects(rgb::normal fillPercent = 1.0f) -> void;
  auto drawRainbowEffects(rgb::normal fillPercent = 1.0f) -> void;
  auto drawSleepEffects(rgb::normal fillPercent = 1.0f) -> void;

  static auto GetFiberBrightness() -> float;

  rgb::Timestamp mLastUpdate{rgb::Timestamp::Zero()};
  rgb::kph mPreviousSpeed{};
  rgb::kph mSpeed{};
  rgb::kph mSmoothSpeed{};
  rgb::percent mThrottle{};
  rgb::percent mSmoothThrottle{};
  rgb::percent mThrottleWhenRainbowStart{};
  rgb::percent mChargeFillPercent{};
  rgb::revs_per_minute mPreviousRpm{};
  rgb::revs_per_minute mRpm{};
  rgb::revs_per_minute mSmoothRpm{};
  rgb::fahrenheit mCoolantTemp{};
  CorvetteState* mState{&SLEEP_STATE};
  rgb::ChasingEffectSpeedOnly chasingEffect;
  rgb::EffectHandle chaseHandle;
};

#endif //RGBLIB_CORVETTE_H
