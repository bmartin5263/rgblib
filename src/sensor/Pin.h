//
// Created by Brandon on 2/20/25.
//

#ifndef RGBLIB_PIN_H
#define RGBLIB_PIN_H

#include "Handle.h"

namespace rgb {

struct TurnOffPin {
  auto operator()(pin_num number) -> void;
};

using Pin = Handle<pin_num, TurnOffPin>;
}


#endif //RGBLIB_PIN_H
