//
// Created by Brandon on 12/8/24.
//

#ifndef NEOPIXELS_LOG_H
#define NEOPIXELS_LOG_H

#include <Arduino.h>
#include "Types.h"

namespace rgb {

class Log2 {
public:

  auto init(u32 baud = 9600) const -> const Log2& {
    Serial.begin(baud);
    return *this;
  }

  auto infoLn(const char* msg) const -> const Log2& {
    Serial.println(msg);
    return *this;
  }

  auto info(const char* msg) const -> const Log2& {
    Serial.print(msg);
    return *this;
  }

  auto infoLn(i32 msg) const -> const Log2& {
    Serial.println(msg);
    return *this;
  }

  auto info(i32 msg) const -> const Log2& {
    Serial.print(msg);
    return *this;
  }

  auto infoLn(float msg) const -> const Log2& {
    Serial.println(msg);
    return *this;
  }

  auto info(float msg) const -> const Log2& {
    Serial.print(msg);
    return *this;
  }

  auto infoLn(u32 msg) const -> const Log2& {
    Serial.println(msg);
    return *this;
  }

  auto info(u32 msg) const -> const Log2& {
    Serial.print(msg);
    return *this;
  }

};

constexpr Log2 Log = {};

}


#endif //NEOPIXELS_LOG_H
