//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_HOSTSYSTEMArduino_H
#define RGBLIB_HOSTSYSTEMArduino_H

#include <Arduino.h>
#include "Types.h"
#include "HostSystemBase.h"

namespace rgb::priv {

class HostSystemArduino : public HostSystemBase {
public:
  auto microTime() -> microseconds_t {
    return micros();
  }

  auto milliTime() -> milliseconds_t {
    return millis();
  }

  auto microSleep(microseconds_t time) -> void {
    return delayMicroseconds(time);
  }

  auto milliSleep(milliseconds_t time) -> void {
    return delay(time);
  }
};


}

#endif //RGBLIB_HOSTSYSTEMArduino_H
