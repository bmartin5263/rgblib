//
// Created by Brandon on 5/13/25.
//

#include "IRReceiver.h"
#include <IRremote.hpp>

namespace rgb {

auto IRReceiver::start(pin_num pin) -> bool {
  IrReceiver.begin(pin, ENABLE_LED_FEEDBACK);
  return true;
}

auto IRReceiver::update() -> void {
  if (IrReceiver.decode()) {
    dispatchEvent(IrReceiver.decodedIRData.decodedRawData);
    IrReceiver.resume();
  }
}

auto IRReceiver::dispatchEvent(uint64_t data) -> void {
  switch (data) {
    case BUTTON_1:
      Serial.println("1");
      on1();
      break;
    case BUTTON_2:
      Serial.println("2");
      on2();
      break;
    case BUTTON_3:
      Serial.println("3");
      on3();
      break;
    case BUTTON_4:
      Serial.println("4");
      on4();
      break;
    case BUTTON_5:
      Serial.println("5");
      on5();
      break;
    case BUTTON_6:
      Serial.println("6");
      on6();
      break;
    case BUTTON_7:
      Serial.println("7");
      on7();
      break;
    case BUTTON_8:
      Serial.println("8");
      on8();
      break;
    case BUTTON_9:
      Serial.println("9");
      on9();
      break;
    case BUTTON_0:
      Serial.println("0");
      on0();
      break;
    case BUTTON_STAR:
      Serial.println("*");
      onStar();
      break;
    case BUTTON_HASH:
      Serial.println("#");
      onHash();
      break;
    case BUTTON_UP:
      Serial.println("up");
      onUp();
      break;
    case BUTTON_DOWN:
      Serial.println("down");
      onDown();
      break;
    case BUTTON_LEFT:
      Serial.println("left");
      onLeft();
      break;
    case BUTTON_RIGHT:
      Serial.println("right");
      onRight();
      break;
    case BUTTON_OK:
      Serial.println("ok");
      onOk();
      break;
  }
}

auto IRReceiver::stop() -> void {
  IrReceiver.stop();
}

}