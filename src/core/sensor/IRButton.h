//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_IRBUTTON_H
#define RGBLIB_IRBUTTON_H


#include <memory>
#include "Func.h"
#include "Types.h"
#include "ButtonState.h"
#include "IRButtonType.h"

namespace rgb {

class IRButton {
  static constexpr auto doNothing() -> void {}

public:
  explicit IRButton(IRButtonType type);
  auto onPress(Runnable callback) noexcept -> IRButton&;

  auto update(IRButtonType pressedType) -> ButtonState;
  auto getState() const noexcept -> ButtonState;

private:
  ButtonState state;
  IRButtonType type;
  Runnable onPressCallback;
};

}


#endif //RGBLIB_IRBUTTON_H
