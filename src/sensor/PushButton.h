//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_PUSHBUTTON_H
#define RGBLIB_PUSHBUTTON_H


#include "Types.h"
#include "ButtonState.h"

namespace rgb {

class PushButton {
public:
  PushButton(pin_num pin);
  auto init() -> PushButton&;
  auto update() -> ButtonState;
  auto getState() -> ButtonState;
  auto wasPressed() -> bool;
  auto isHeldDown() -> bool;

private:
  ButtonState state;
  u16 timeInState;
  u16 repeatDelay;
  pin_num pin;
};

}


#endif //RGBLIB_PUSHBUTTON_H
