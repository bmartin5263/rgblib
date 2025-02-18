//
// Created by Brandon on 12/8/24.
//

#ifndef NEOPIXELS_LOG_H
#define NEOPIXELS_LOG_H

#include <Arduino.h>
#include "Types.h"

namespace rgb {

class Log {
public:

  static auto Init(u32 baud = 9600) -> Log& {
    return Instance().init(baud);
  }

  static auto InfoLn(const char* msg) -> Log& {
    return Instance().infoLn(msg);
  }

  static auto Info(const char* msg) -> Log& {
    return Instance().info(msg);
  }

  static auto InfoLn(i32 msg) -> Log& {
    return Instance().infoLn(msg);
  }

  static auto Info(i32 msg) -> Log& {
    return Instance().info(msg);
  }

  static auto InfoLn(float msg) -> Log& {
    return Instance().infoLn(msg);
  }

  static auto Info(float msg) -> Log& {
    return Instance().info(msg);
  }

  static auto InfoLn(u32 msg) -> Log& {
    return Instance().infoLn(msg);
  }

  static auto Info(u32 msg) -> Log& {
    return Instance().info(msg);
  }

  auto init(u32 baud) -> Log& {
    Serial.begin(baud);
    return *this;
  }

  auto infoLn(const char* msg) -> Log& {
    Serial.println(msg);
    return *this;
  }

  auto info(const char* msg) -> Log& {
    Serial.print(msg);
    return *this;
  }

  auto infoLn(i32 msg) -> Log& {
    Serial.println(msg);
    return *this;
  }

  auto info(i32 msg) -> Log& {
    Serial.print(msg);
    return *this;
  }

  auto infoLn(float msg) -> Log& {
    Serial.println(msg);
    return *this;
  }

  auto info(float msg) -> Log& {
    Serial.print(msg);
    return *this;
  }

  auto infoLn(u32 msg) -> Log& {
    Serial.println(msg);
    return *this;
  }

  auto info(u32 msg) -> Log& {
    Serial.print(msg);
    return *this;
  }

private:
  static Log& Instance() {
    static Log instance;
    return instance;
  }


};

}


#endif //NEOPIXELS_LOG_H
