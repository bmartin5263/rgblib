//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_CLOCKARDUINO_H
#define RGBLIB_CLOCKARDUINO_H

#include <Arduino.h>
#include "ClockBase.h"
#include "Types.h"

namespace rgb::priv {

class ClockArduino : public ClockBase {
public:
  auto start() -> void {
    lastWakeTime = xTaskGetTickCount();
    resetTiming();
  }

  auto nextFrame() -> void {
    xTaskDelayUntil(&lastWakeTime, frequency);
    recordFrame();
  }

private:
  uint lastWakeTime{xTaskGetTickCount()};
  u64 frequency{pdMS_TO_TICKS(4)}; // ~200 FPS
};

}

#endif //RGBLIB_CLOCKARDUINO_H
