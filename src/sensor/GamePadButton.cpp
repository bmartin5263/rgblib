//
// Created by Brandon on 2/17/25.
//

#include <utility>
#include "GamePadButton.h"

namespace rgb {

GamePadButton::GamePadButton()
  : state(ButtonState::UNPRESSED), onPressCallback(doNothing)
{
}

auto GamePadButton::onPress(Runnable callback) noexcept -> GamePadButton& {
  onPressCallback = std::move(callback);
  return *this;
}

auto GamePadButton::update(bool pressed) -> ButtonState {
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

auto GamePadButton::getState() const noexcept -> ButtonState {
  return state;
}

}