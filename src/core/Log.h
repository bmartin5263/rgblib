//
// Created by Brandon on 12/8/24.
//

#ifndef NEOPIXELS_LOG_H
#define NEOPIXELS_LOG_H

#include <Arduino.h>
#include "Types.h"

class Log {
public:

  static auto Init(u32 baud = 9600) -> void {
    Serial.begin(baud);
  }

  static auto InfoLn(const char* msg) -> void {
    Serial.println(msg);
  }

  static auto Info(const char* msg) -> void {
    Serial.print(msg);
  }

  static auto InfoLn(i32 msg) -> void {
    Serial.println(msg);
  }

  static auto Info(i32 msg) -> void {
    Serial.print(msg);
  }

  static auto InfoLn(float msg) -> void {
    Serial.println(msg);
  }

  static auto Info(float msg) -> void {
    Serial.print(msg);
  }

  static auto InfoLn(u32 msg) -> void {
    Serial.println(msg);
  }

  static auto Info(u32 msg) -> void {
    Serial.print(msg);
  }

};

#endif //NEOPIXELS_LOG_H
