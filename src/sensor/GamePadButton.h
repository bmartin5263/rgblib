//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_GAMEPADBUTTON_H
#define RGBLIB_GAMEPADBUTTON_H


#include <memory>
#include "Func.h"
#include "Types.h"
#include "ButtonState.h"

namespace rgb {

class GamePadButton {
  static constexpr auto doNothing() -> void {}

public:
  explicit GamePadButton();
  auto onPress(Runnable callback) noexcept -> GamePadButton&;

  auto update(bool pressed) -> ButtonState;
  auto getState() const noexcept -> ButtonState;
  auto isPressed() const noexcept -> bool { return state == ButtonState::PRESS || state == ButtonState::PRESSED; };

private:
  ButtonState state;
  Runnable onPressCallback;
};

}


#endif //RGBLIB_GAMEPADBUTTON_H
