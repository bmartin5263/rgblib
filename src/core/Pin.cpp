//
// Created by Brandon on 10/6/25.
//

#include "Pin.h"

namespace rgb {

auto TurnOffPin::operator()(PinNumber number) -> void {
  TRACE("TurnOffPin();");
//  pinMode(number, LOW); TODO
}

}