//
// Created by Brandon on 5/13/25.
//

#ifndef RGBLIB_IRREMOTE_H
#define RGBLIB_IRREMOTE_H

#include <functional>
#include "Types.h"

namespace rgb {

class IRReceiver {
  static constexpr auto doNothing() -> void {};

public:
  auto start(pin_num pin) -> bool;
  auto update() -> void;
  auto stop() -> void;

  std::function<void()> on0{doNothing};
  std::function<void()> on1{doNothing};
  std::function<void()> on2{doNothing};
  std::function<void()> on3{doNothing};
  std::function<void()> on4{doNothing};
  std::function<void()> on5{doNothing};
  std::function<void()> on6{doNothing};
  std::function<void()> on7{doNothing};
  std::function<void()> on8{doNothing};
  std::function<void()> on9{doNothing};
  std::function<void()> onUp{doNothing};
  std::function<void()> onRight{doNothing};
  std::function<void()> onDown{doNothing};
  std::function<void()> onLeft{doNothing};
  std::function<void()> onStar{doNothing};
  std::function<void()> onHash{doNothing};
  std::function<void()> onOk{doNothing};

  constexpr static auto BUTTON_1 = 0xBA45FF00;
  constexpr static auto BUTTON_2 = 0xB946FF00;
  constexpr static auto BUTTON_3 = 0xB847FF00;
  constexpr static auto BUTTON_4 = 0xBB44FF00;
  constexpr static auto BUTTON_5 = 0xBF40FF00;
  constexpr static auto BUTTON_6 = 0xBC43FF00;
  constexpr static auto BUTTON_7 = 0xF807FF00;
  constexpr static auto BUTTON_8 = 0xEA15FF00;
  constexpr static auto BUTTON_9 = 0xF609FF00;
  constexpr static auto BUTTON_0 = 0xE619FF00;
  constexpr static auto BUTTON_UP = 0xE718FF00;
  constexpr static auto BUTTON_RIGHT = 0xA55AFF00;
  constexpr static auto BUTTON_DOWN = 0xAD52FF00;
  constexpr static auto BUTTON_LEFT = 0xF708FF00;
  constexpr static auto BUTTON_STAR = 0xE916FF00;
  constexpr static auto BUTTON_HASH = 0xF20DFF00;
  constexpr static auto BUTTON_OK = 0xE31CFF00;

private:
  auto dispatchEvent(uint64_t data) -> void;

};

}


#endif //RGBLIB_IRREMOTE_H
