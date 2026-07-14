//
// Created by Brandon on 2/4/26.
//

#ifndef RGBLIB_CORVETTESTATE_H
#define RGBLIB_CORVETTESTATE_H

#include "Types.h"

class Corvette;
class CorvetteState {
public:
  virtual auto update(Corvette& vehicle) -> void = 0;
  virtual auto draw(Corvette& vehicle) -> void {}

  CorvetteState() = default;
  CorvetteState(const CorvetteState& rhs) = default;
  CorvetteState(CorvetteState&& rhs) noexcept = default;
  CorvetteState& operator=(const CorvetteState& rhs) = default;
  CorvetteState& operator=(CorvetteState&& rhs) noexcept = default;
  virtual ~CorvetteState() = default;

  rgb::Timestamp enteredAt;
  rgb::Timestamp effectiveStartTime;
};

class IdleState : public CorvetteState {
public:
  auto reset(rgb::Timestamp enteredAt) -> void;
  auto update(Corvette& vehicle) -> void override;
  auto draw(Corvette& vehicle) -> void override;
};

class ColdStartState : public IdleState {
public:
  auto reset(rgb::Timestamp enteredAt) -> void;
  auto update(Corvette& vehicle) -> void override;
  auto draw(Corvette& vehicle) -> void override;
};

class DrivingState : public CorvetteState {
public:
  auto reset(rgb::Timestamp enteredAt, bool chargeUp) -> void;
  auto update(Corvette& vehicle) -> void override;
  auto draw(Corvette& vehicle) -> void override;

  bool chargeUp;
};

class RainbowState : public DrivingState {
public:
  auto reset(rgb::Timestamp enteredAt, rgb::percent throttleWhenRainbowStart) -> void;
  auto update(Corvette& vehicle) -> void override;
  auto draw(Corvette& vehicle) -> void override;

  rgb::percent throttleWhenRainbowStart;
};


#endif //RGBLIB_CORVETTESTATE_H
