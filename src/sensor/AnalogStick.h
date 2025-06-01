//
// Created by Brandon on 5/31/25.
//

#ifndef RGBLIB_ANALOGSTICK_H
#define RGBLIB_ANALOGSTICK_H

#include "Types.h"
#include "PushButton.h"

namespace rgb {

class AnalogStick {
public:
  AnalogStick(pin_num xPinNum, pin_num yPinNum, pin_num buttonPinNum);

  auto readX() -> u16;
  auto readY() -> u16;
  auto update() -> void;

private:
  Pin xPin;
  Pin yPin;
  PushButton button;

};


}

#endif //RGBLIB_ANALOGSTICK_H
