//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_UTIL_H
#define RGBLIB_UTIL_H

#include "Types.h"
#include "Assertions.h"

#define MAX(a, b) \
    ({ auto _a = (a); auto _b = (b); _a > _b ? _a : _b; })

#define MIN(a, b) \
    ({ auto _a = (a); auto _b = (b); _a < _b ? _a : _b; })

auto ExtractBytes(u32 input, u8& byte0, u8& byte1, u8& byte2, u8& byte3) -> void;
auto Clamp(float value) -> float;
auto Sigmoid(u32 value) -> float;
auto Lerp(float a, float b, float t) -> float;
auto LerpWrap(float a, float b, float t) -> float;
auto LerpClamp(float a, float b, float t) -> float;

#endif //RGBLIB_UTIL_H
