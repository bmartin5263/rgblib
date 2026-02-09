//
// Created by Brandon on 2/4/26.
//

#ifndef RGBLIB_LINCOLNTOWNCARSTATE_H
#define RGBLIB_LINCOLNTOWNCARSTATE_H

#include "Types.h"

class LincolnTownCar;
class LincolnTownCarState {
public:
  virtual auto reset(LincolnTownCar& vehicle) -> void {};
  virtual auto update(LincolnTownCar& vehicle) -> void = 0;

  LincolnTownCarState() = default;
  LincolnTownCarState(const LincolnTownCarState& rhs) = default;
  LincolnTownCarState(LincolnTownCarState&& rhs) noexcept = default;
  LincolnTownCarState& operator=(const LincolnTownCarState& rhs) = default;
  LincolnTownCarState& operator=(LincolnTownCarState&& rhs) noexcept = default;
  virtual ~LincolnTownCarState() = default;
};

class StoppedState : public LincolnTownCarState {
public:
  auto reset(LincolnTownCar& vehicle) -> void override;
  auto update(LincolnTownCar& vehicle) -> void override;
};

class ColdStartState : public LincolnTownCarState {
public:
  auto update(LincolnTownCar& vehicle) -> void override;

};

class MovingState : public LincolnTownCarState {
public:
  auto reset(LincolnTownCar& vehicle) -> void override;
  auto update(LincolnTownCar& vehicle) -> void override;
};


#endif //RGBLIB_LINCOLNTOWNCARSTATE_H
