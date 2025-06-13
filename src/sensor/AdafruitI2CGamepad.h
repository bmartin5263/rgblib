//
// Created by Brandon on 6/12/25.
//

#ifndef RGBLIB_ADAFRUITI2CGAMEPAD_H
#define RGBLIB_ADAFRUITI2CGAMEPAD_H

#include "Types.h"
#include "Func.h"
#include "MyAdafruitSeesaw.h"
#include "GamePadButton.h"

namespace rgb {

class AdafruitI2CGamepad {
  constexpr static auto doNothing() -> void {}
public:
  auto start() -> void;
  auto update() -> void;

  Adafruit_seesaw seesaw;
  GamePadButton buttonX{};
  GamePadButton buttonY{};
  GamePadButton buttonA{};
  GamePadButton buttonB{};
  GamePadButton buttonStart{};
  GamePadButton buttonSelect{};
  normal analogX{};
  normal analogY{};
};

}


#endif //RGBLIB_ADAFRUITI2CGAMEPAD_H
