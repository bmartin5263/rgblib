//
// Created by Brandon on 3/26/25.
//

#include "Log.h"
#include <Arduino.h>
#include <cstdarg>
#include <cstdio>

namespace rgb::log {
bool initialized = false;

auto init(u32 baud) -> void {
  if (!initialized) {
    Serial.begin(baud);
    initialized = true;
  }
}

constexpr static auto MS_PER_HOUR = 1000 * 60 * 60;
constexpr static auto MS_PER_MINUTE = 1000 * 60;
constexpr static auto MS_PER_SECOND = 1000;

// Single transient stack buffer per log call. Output longer than this is
// truncated rather than spilling to the heap, keeping logging allocation-free.
constexpr static size_t BUFFER_SIZE = 256;

static auto writeBuffer(const char* buffer, int length) -> void {
  if (length <= 0) {
    return;
  }
  auto written = static_cast<size_t>(length) < BUFFER_SIZE
    ? static_cast<size_t>(length)
    : BUFFER_SIZE - 1;
  Serial.write(reinterpret_cast<const uint8_t*>(buffer), written);
}

auto printHeader(const char* level, const char* function) -> void {
  auto milliseconds = millis();
  auto hours = milliseconds / MS_PER_HOUR;
  milliseconds %= MS_PER_HOUR;
  auto minutes = milliseconds / MS_PER_MINUTE;
  milliseconds %= MS_PER_MINUTE;
  auto seconds = milliseconds / MS_PER_SECOND;
  milliseconds %= MS_PER_SECOND;

  char buffer[BUFFER_SIZE];
  auto length = snprintf(
    buffer, sizeof(buffer),
    "%02lu:%02lu:%02lu.%03lu [%-5s] [%-60s] : ",
    hours, minutes, seconds, milliseconds, level, function
  );
  writeBuffer(buffer, length);
}

auto printMessage(const char* format, ...) -> void {
  char buffer[BUFFER_SIZE];

  va_list args;
  va_start(args, format);
  auto length = vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  writeBuffer(buffer, length);

  static constexpr char newline[] = "\r\n";
  Serial.write(reinterpret_cast<const uint8_t*>(newline), sizeof(newline) - 1);
}

}
