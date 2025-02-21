//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_PUSHBUTTON_H
#define RGBLIB_PUSHBUTTON_H


#include <memory>
#include "Types.h"
#include "Pin.h"
#include "ButtonState.h"

namespace rgb {

class PushButton {
  using PressCallback = std::function<void()>;

public:
  explicit PushButton(pin_num pin);
  auto onPress(PressCallback callback) noexcept -> PushButton&;

  auto update() -> ButtonState;

  auto getState() const noexcept -> ButtonState;

private:
  ButtonState state;
  Pin pin;
  PressCallback onPressCallback;
};

}


#endif //RGBLIB_PUSHBUTTON_H
