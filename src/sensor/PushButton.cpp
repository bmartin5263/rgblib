//
// Created by Brandon on 2/17/25.
//

#include <Arduino.h>

#include <utility>
#include "PushButton.h"
#include "Log.h"

namespace rgb {

PushButton::PushButton(pin_num pin)
  : state(ButtonState::UNPRESSED), pin(pin), onPressCallback(doNothing)
{
  pinMode(pin, INPUT);
}

PushButton::PushButton(pin_num pin, PressCallback callback)
  : state(ButtonState::UNPRESSED), pin(pin), onPressCallback(std::move(callback))
{
  pinMode(pin, INPUT);
}

auto PushButton::onPress(PressCallback callback) noexcept -> PushButton& {
  onPressCallback = std::move(callback);
  return *this;
}

// TODO - must be called every frame, but easy to forget
auto PushButton::update() -> ButtonState {
  auto pressed = digitalRead(*pin);
  if (state == ButtonState::UNPRESSED || state == ButtonState::UNPRESS) {
    if (pressed) {
      if (onPressCallback) {
        onPressCallback();
      }
      state = ButtonState::PRESS;
    }
    else {
      state = ButtonState::UNPRESSED;
    }
  }
  else if (state == ButtonState::PRESS || state == ButtonState::PRESSED) {
    state = pressed ? ButtonState::PRESSED : ButtonState::UNPRESS;
  }

  return state;
}

auto PushButton::getState() const noexcept -> ButtonState {
  return state;
}

}