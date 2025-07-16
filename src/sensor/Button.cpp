//
// Created by Brandon on 7/15/25.
//

#include "Button.h"

namespace rgb {

Button::Button()
  : state(ButtonState::UNPRESSED), onPressCallback(DoNothing)
{
}

Button::Button(Runnable callback)
  : state(ButtonState::UNPRESSED), onPressCallback(std::move(callback))
{
}

auto Button::onPress(Runnable callback) noexcept -> Button& {
  onPressCallback = std::move(callback);
  return *this;
}

auto Button::update(bool pressed) -> ButtonState {
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

auto Button::getState() const noexcept -> ButtonState {
  return state;
}

}