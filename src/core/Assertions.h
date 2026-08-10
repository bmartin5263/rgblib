//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_ASSERT_H
#define RGBLIB_ASSERT_H

//#ifndef NDEBUG
#include "Debug.h"
#include "Log.h"
#define FAIL(message) \
        do { \
          printf("Failure Detected\n");      \
          printf("File: %s, Function: %s, Line: %i, Message: %s\n", __FILE__, __FUNCTION__, __LINE__, message);                   \
          rgb::Debug::TriggerFault();                                    \
        } while (false)

#define ASSERT(condition, message) \
        do { \
            if (!(condition)) {    \
                printf("Assertion failed: (%s)\n", #condition);                   \
                printf("File: %s, Function: %s, Line: %i, Message: %s\n", __FILE__, __FUNCTION__, __LINE__, message);                   \
                rgb::Debug::TriggerFault();                                    \
            } \
        } while (false)

#endif //RGBLIB_ASSERT_H
