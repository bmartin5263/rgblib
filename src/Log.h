//
// Created by Brandon on 12/8/24.
//

#ifndef NEOPIXELS_LOG_H
#define NEOPIXELS_LOG_H

#include <Arduino.h>
#include "Types.h"

namespace rgb {

class Logger {
public:

  auto init(u32 baud = 9600) const -> void {
    Serial.begin(baud);
  }

  template<class T>
  auto info(T msg) const -> const Logger& {
    Serial.print(msg);
    return *this;
  }

  template<class T>
  auto infoLn(T msg) const -> const Logger& {
    Serial.println(msg);
    return *this;
  }

};

constexpr Logger Log = {};

}


#endif //NEOPIXELS_LOG_H
