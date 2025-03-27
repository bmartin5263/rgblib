//
// Created by Brandon on 2/20/25.
//

#include "Pin.h"
#include "Log.h"

namespace rgb {

auto TurnOffPin::operator()(pin_num number) -> void {
  TRACE("TurnOffPin();");
  pinMode(number, LOW);
}

}