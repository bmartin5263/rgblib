//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_ASSERT_H
#define RGBLIB_ASSERT_H

//#ifndef NDEBUG
#include "Debug.h"
#include "Log.h"
#define ASSERT(condition, message) \
        do { \
            if (!(condition)) {    \
                Log.infoLn("Assertion failed: (" #condition ")"); \
                Log.info("File: "); \
                Log.info(__FILE__); \
                Log.info(", Line: "); \
                Log.infoLn((u32) __LINE__); \
                Log.info("Message: "); \
                Log.infoLn(message);                              \
                Debug::Instance().trigger(true);                   \
            } \
        } while (false)
//#else
//#define ASSERT(condition, message) ((void)0) // No-op in release builds
//#endif

#endif //RGBLIB_ASSERT_H
