//
// Created by Brandon on 5/31/25.
//

#include "AnalogStick.h"

namespace rgb {

AnalogStick::AnalogStick(rgb::pin_num xPinNum, rgb::pin_num yPinNum, rgb::pin_num buttonPinNum)
  : xPin(xPinNum), yPin(yPinNum), button(buttonPinNum)
{
}

auto AnalogStick::readX() -> u16 {
  return analogRead(*xPin);
}

auto AnalogStick::readY() -> u16 {
  return analogRead(*yPin);
}

auto AnalogStick::update() -> void {
  button.update();
}

}