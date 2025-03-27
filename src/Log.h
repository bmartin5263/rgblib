//
// Created by Brandon on 12/8/24.
//

#ifndef NEOPIXELS_LOG_H
#define NEOPIXELS_LOG_H

#include <Arduino.h>
#include "Types.h"

namespace rgb::log {

constexpr auto MS_PER_HOUR = 1000 * 60 * 60;
constexpr auto MS_PER_MINUTE = 1000 * 60;
constexpr auto MS_PER_SECOND = 1000;

auto init(u32 baud = 9600) -> void;
auto printHeader(const char* level, const char* function) -> void;

#if defined (RGB_VERBOSE)
#define TRACE(format, ...) do { \
  rgb::log::printHeader("TRACE", __PRETTY_FUNCTION__);  \
  Serial.printf(format, ##__VA_ARGS__); \
  Serial.println();            \
} while(false)
#else
#define TRACE(format, ...)
#endif


#if defined (RGB_DEBUG) || defined (RGB_VERBOSE)

#define INFO(format, ...) do { \
  rgb::log::printHeader("INFO", __PRETTY_FUNCTION__);  \
  Serial.printf(format, ##__VA_ARGS__); \
  Serial.println();            \
} while(false)

#define ERROR(format, ...) do { \
  rgb::log::printHeader("ERROR", __PRETTY_FUNCTION__);  \
  Serial.printf(format, ##__VA_ARGS__); \
  Serial.println();            \
} while(false)

#else
#define INFO(format, ...)
#define ERROR(format, ...)
#endif

}


#endif //NEOPIXELS_LOG_H
