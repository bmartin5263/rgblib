//
// Created by Brandon on 3/26/25.
//

#include "Log.h"
#include "System.h"
#include <cstdarg>
#include <cstdio>

#if defined(RGB_ARDUINO_ESP32)
#include <Arduino.h>
#endif

namespace rgb::log {
bool initialized = false;

auto init(u32 baud) -> void {
#if defined(RGB_ARDUINO_ESP32)
  if (!initialized) {
    Serial.begin(baud);
    initialized = true;
  }
#else
  initialized = true;
#endif
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
#if defined(RGB_ARDUINO_ESP32)
  Serial.write(reinterpret_cast<const uint8_t*>(buffer), written);
#else
  std::fwrite(buffer, 1, written, stdout);
#endif
}

auto printHeader(const char* level, const char* function) -> void {
  auto milliseconds = System::MilliTime();
  auto hours = milliseconds / MS_PER_HOUR;
  milliseconds %= MS_PER_HOUR;
  auto minutes = milliseconds / MS_PER_MINUTE;
  milliseconds %= MS_PER_MINUTE;
  auto seconds = milliseconds / MS_PER_SECOND;
  milliseconds %= MS_PER_SECOND;

  char buffer[BUFFER_SIZE];
  auto length = snprintf(
    buffer, sizeof(buffer),
    "%02llu:%02llu:%02llu.%03llu [%-5s] [%-60s] : ",
    static_cast<unsigned long long>(hours),
    static_cast<unsigned long long>(minutes),
    static_cast<unsigned long long>(seconds),
    static_cast<unsigned long long>(milliseconds),
    level, function
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
#if defined(RGB_ARDUINO_ESP32)
  Serial.write(reinterpret_cast<const uint8_t*>(newline), sizeof(newline) - 1);
#else
  std::fwrite(newline, 1, sizeof(newline) - 1, stdout);
#endif
}

}
