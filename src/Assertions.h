//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_ASSERT_H
#define RGBLIB_ASSERT_H

//#ifndef NDEBUG
#include "Debug.h"
#include "Log.h"
#include "DebugScreen.h"
#define FAIL(message, color) \
        do { \
          Serial.printf("Failure Detected\n");      \
          Serial.printf("File: %s, Function: %s, Line: %i, Message: %s\n", __FILE__, __FUNCTION__, __LINE__, message);                   \
          rgb::Debug::Trigger(color);                                    \
          rgb::DebugScreen::PrintLine(0, message);                   \
        } while (false)

#define ASSERT(condition, message) \
        do { \
            if (!(condition)) {    \
                Serial.printf("Assertion failed: (%s)\n", #condition);                   \
                Serial.printf("File: %s, Function: %s, Line: %i, Message: %s\n", __FILE__, __FUNCTION__, __LINE__, message);                   \
                rgb::Debug::Trigger();                                    \
                rgb::DebugScreen::PrintLine(0, message);                   \
            } \
        } while (false)

#define ASSERT_C(condition, message, color) \
        do { \
            if (!(condition)) {    \
                Serial.printf("Assertion failed: (%s)\n", #condition);                   \
                Serial.printf("File: %s, Function: %s, Line: %i, Message: %s\n", __FILE__, __FUNCTION__, __LINE__, message);                   \
                rgb::Debug::Trigger(color);                                    \
                rgb::DebugScreen::PrintLine(0, message);                   \
            } \
        } while (false)
//#else
//#define ASSERT(condition, message) ((void)0) // No-op in release builds
//#endif

#endif //RGBLIB_ASSERT_H
