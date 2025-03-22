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

  auto init(u32 baud = 9600) -> void {
    Serial.begin(baud);
  }

  template<class T>
  auto info(T msg) -> Logger& {
    if (newLine) {
      printTime();
      newLine = false;
    }
    Serial.print(msg);
    return *this;
  }

  template<class T>
  auto infoLn(T msg) -> Logger& {
    if (newLine) {
      printTime();
    }
    Serial.println(msg);
    newLine = true;
    return *this;
  }

  template<class T>
  auto error(T msg) -> Logger& {
    return info(msg);
  }

  template<class T>
  auto errorLn(T msg) -> Logger& {
    return errorLn(msg);
  }

private:
  auto printTime() -> void {
    Serial.print(millis());
    Serial.print(": ");
  }

private:
  bool newLine{true};

};

static Logger Log = {};

#define INFO(message) \
  do {                \
    Log.info(__FILE__); \
        .info("("); \
        .info(__LINE__); \
        .info(") : "); \
        .info(millis()); \
        .info(": "); \
        .infoLn(message);   \
  } while (false)

}


#endif //NEOPIXELS_LOG_H
