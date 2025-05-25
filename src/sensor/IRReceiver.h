//
// Created by Brandon on 5/13/25.
//

#ifndef RGBLIB_IRREMOTE_H
#define RGBLIB_IRREMOTE_H

#include <functional>
#include "Types.h"
#include "PushButton.h"
#include "IRButton.h"

namespace rgb {

class IRReceiver {
  static constexpr auto doNothing() -> void {};

public:
  auto start(pin_num pin) -> bool;
  auto update() -> void;
  auto stop() -> void;

  IRButton button0{IRButtonType::BUTTON_0};
  IRButton button1{IRButtonType::BUTTON_1};
  IRButton button2{IRButtonType::BUTTON_2};
  IRButton button3{IRButtonType::BUTTON_3};
  IRButton button4{IRButtonType::BUTTON_4};
  IRButton button5{IRButtonType::BUTTON_5};
  IRButton button6{IRButtonType::BUTTON_6};
  IRButton button7{IRButtonType::BUTTON_7};
  IRButton button8{IRButtonType::BUTTON_8};
  IRButton button9{IRButtonType::BUTTON_9};
  IRButton buttonUp{IRButtonType::BUTTON_UP};
  IRButton buttonRight{IRButtonType::BUTTON_RIGHT};
  IRButton buttonDown{IRButtonType::BUTTON_DOWN};
  IRButton buttonLeft{IRButtonType::BUTTON_LEFT};
  IRButton buttonStar{IRButtonType::BUTTON_STAR};
  IRButton buttonHash{IRButtonType::BUTTON_HASH};
  IRButton buttonOk{IRButtonType::BUTTON_OK};
};

}


#endif //RGBLIB_IRREMOTE_H
