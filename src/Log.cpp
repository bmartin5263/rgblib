//
// Created by Brandon on 3/26/25.
//

#include "Log.h"
#include "Arduino.h"

namespace rgb::log {

auto init(u32 baud) -> void {
  Serial.begin(baud);
}

auto printHeader(const char* level, const char* function) -> void {
  auto milliseconds = millis();
  auto hours = milliseconds / MS_PER_HOUR;
  milliseconds %= MS_PER_HOUR;
  auto minutes = milliseconds / MS_PER_MINUTE;
  milliseconds %= MS_PER_MINUTE;
  auto seconds = milliseconds / MS_PER_SECOND;
  milliseconds %= MS_PER_SECOND;
  Serial.printf("%02lu:%02lu:%02lu.%03lu [%-5s] [%-60s] : ", hours, minutes, seconds, milliseconds, level, function);
}

}