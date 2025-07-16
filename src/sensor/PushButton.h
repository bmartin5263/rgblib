//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_PUSHBUTTON_H
#define RGBLIB_PUSHBUTTON_H


#include <memory>
#include "Types.h"
#include "Func.h"
#include "Pin.h"
#include "Button.h"

namespace rgb {

class PushButton {
  static constexpr auto doNothing() -> void {}

public:
  explicit PushButton(pin_num pin);
  PushButton(pin_num pin, Runnable callback);
  auto onPress(const Runnable& callback) noexcept -> PushButton&;

  auto update() -> ButtonState;
  auto getState() const noexcept -> ButtonState;

private:
  Pin pin;
  Button button;
};

}


#endif //RGBLIB_PUSHBUTTON_H
