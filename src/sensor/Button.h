//
// Created by Brandon on 7/15/25.
//

#ifndef RGBLIB_ABSTRACTBUTTON_H
#define RGBLIB_ABSTRACTBUTTON_H

#include "Func.h"
#include "ButtonState.h"

namespace rgb {

class Button {
  static constexpr auto DoNothing() -> void {}

public:
  explicit Button();
  explicit Button(Runnable callback);
  auto onPress(Runnable callback) noexcept -> Button&;

  auto update(bool pressed) -> ButtonState;
  auto getState() const noexcept -> ButtonState;

private:
  ButtonState state;
  Runnable onPressCallback;
};

}

#endif //RGBLIB_ABSTRACTBUTTON_H
