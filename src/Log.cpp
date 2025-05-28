//
// Created by Brandon on 3/26/25.
//

#include "Log.h"
#include "Arduino.h"
#include "DebugScreen.h"

namespace rgb::log {
bool initialized = false;

auto init(u32 baud) -> void {
  if (!initialized) {
    Serial.begin(baud);
  }
}

constexpr static auto MS_PER_HOUR = 1000 * 60 * 60;
constexpr static auto MS_PER_MINUTE = 1000 * 60;
constexpr static auto MS_PER_SECOND = 1000;

auto printHeader(const char* level, const char* function) -> void {
  auto milliseconds = millis();
  auto hours = milliseconds / MS_PER_HOUR;
  milliseconds %= MS_PER_HOUR;
  auto minutes = milliseconds / MS_PER_MINUTE;
  milliseconds %= MS_PER_MINUTE;
  auto seconds = milliseconds / MS_PER_SECOND;
  milliseconds %= MS_PER_SECOND;
  Serial.printf("%02lu:%02lu:%02lu.%03lu [%-5s] [%-60s] : ", hours, minutes, seconds, milliseconds, level, function);
  rgb::DebugScreen::PrintLine(function); \
}

}