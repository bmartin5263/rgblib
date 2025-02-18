//
// Created by Brandon on 2/17/25.
//

#include <Arduino.h>
#include "PushButton.h"

namespace rgb {

PushButton::PushButton(pin_num pin)
  : state(ButtonState::UNPRESSED), timeInState(0), repeatDelay(0), pin(pin)
{
}

auto PushButton::init() -> PushButton& {
  pinMode(pin, INPUT);
  return *this;
}

auto PushButton::update() -> ButtonState {
  timeInState += 1;

  auto pressed = digitalRead(pin);
  if (state == ButtonState::UNPRESSED || state == ButtonState::UNPRESS) {
    state = pressed ? ButtonState::PRESS : ButtonState::UNPRESSED;
  }
  else if (state == ButtonState::PRESS || state == ButtonState::PRESSED) {
    state = pressed ? ButtonState::PRESSED : ButtonState::UNPRESS;
  }

  return state;
}

auto PushButton::getState() -> ButtonState {
  return state;
}

auto PushButton::isHeldDown() -> bool {
  return wasPressed() || state == ButtonState::PRESSED;
}

auto PushButton::wasPressed() -> bool {
  return state == ButtonState::PRESS;
}

}