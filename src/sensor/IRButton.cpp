//
// Created by Brandon on 2/17/25.
//

#include <utility>
#include "IRButton.h"

namespace rgb {

IRButton::IRButton(IRButtonType type)
  : state(ButtonState::UNPRESSED), type(type), onPressCallback(doNothing)
{
}

auto IRButton::onPress(PressCallback callback) noexcept -> IRButton& {
  onPressCallback = std::move(callback);
  return *this;
}

auto IRButton::update(IRButtonType pressedType) -> ButtonState {
  auto pressed = pressedType == type;
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

auto IRButton::getState() const noexcept -> ButtonState {
  return state;
}

}