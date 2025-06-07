//
// Created by Brandon on 5/13/25.
//

#include "IRReceiver.h"

#undef LOCAL_TRACE
#undef LOCAL_DEBUG
#undef DEBUG
#undef TRACE
#include <IRremote.hpp>

namespace rgb {

auto IRReceiver::start(pin_num pin) -> bool {
  IrReceiver.begin(pin, ENABLE_LED_FEEDBACK);
  return true;
}

auto IRReceiver::update() -> void {
  if (IrReceiver.decode()) {
    auto data = static_cast<IRButtonType>(IrReceiver.decodedIRData.decodedRawData);
    INFO("%i", data);
    button0.update(data);
    button1.update(data);
    button2.update(data);
    button3.update(data);
    button4.update(data);
    button5.update(data);
    button6.update(data);
    button7.update(data);
    button8.update(data);
    button9.update(data);
    buttonUp.update(data);
    buttonRight.update(data);
    buttonDown.update(data);
    buttonLeft.update(data);
    buttonStar.update(data);
    buttonHash.update(data);
    buttonOk.update(data);
    IrReceiver.resume();
  }
}

auto IRReceiver::stop() -> void {
  IrReceiver.stop();
}

}