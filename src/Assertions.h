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
                rgb::Log.infoLn("Assertion failed: (" #condition ")") \
                    .info("File: ") \
                    .info(__FILE__) \
                    .info(", Line: ") \
                    .info((rgb::u32) __LINE__) \
                    .info("Message: ") \
                    .infoLn(message);                              \
                rgb::Debug::Instance().trigger(true);                   \
            } \
        } while (false)
//#else
//#define ASSERT(condition, message) ((void)0) // No-op in release builds
//#endif

#endif //RGBLIB_ASSERT_H
