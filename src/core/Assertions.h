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
                Log::InfoLn("Assertion failed: (" #condition ")"); \
                Log::Info("File: "); \
                Log::Info(__FILE__); \
                Log::Info(", Line: "); \
                Log::InfoLn((unsigned long) __LINE__); \
                Log::Info("Message: "); \
                Log::InfoLn(message);                              \
                Debug::Instance()->trigger(true);                   \
            } \
        } while (false)
//#else
//#define ASSERT(condition, message) ((void)0) // No-op in release builds
//#endif

#endif //RGBLIB_ASSERT_H
