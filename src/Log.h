//
// Created by Brandon on 12/8/24.
//

#ifndef NEOPIXELS_LOG_H
#define NEOPIXELS_LOG_H

#include <Arduino.h>
#include "Types.h"

#if defined (RGB_DEBUG)
#if !defined(RGB_LOG_LEVEL)
#define RGB_LOG_LEVEL 1
#endif
#endif

namespace rgb::log {

auto init(u32 baud = 9600) -> void;
auto printHeader(const char* level, const char* function) -> void;

#define ERROR(format, ...) do { \
  rgb::log::printHeader("ERROR", __PRETTY_FUNCTION__); \
  Serial.printf(format, ##__VA_ARGS__); \
  Serial.println();            \
} while(false)

#define PRINTF(format, ...) do { \
  Serial.printf(format, ##__VA_ARGS__); \
  Serial.println();            \
} while(false)

#if RGB_LOG_LEVEL > 0
#define INFO(format, ...) do { \
  rgb::log::printHeader("INFO", __FUNCTION__);  \
  Serial.printf(format, ##__VA_ARGS__);                \
  Serial.println();            \
} while(false)
#else
#define INFO(format, ...)
#endif


#if RGB_LOG_LEVEL > 1
#define TRACE(format, ...) do { \
  rgb::log::printHeader("TRACE", __PRETTY_FUNCTION__); \
  Serial.printf(format, ##__VA_ARGS__); \
  Serial.println();            \
} while(false)
#else
#define TRACE(format, ...)
#endif

}


#endif //NEOPIXELS_LOG_H
