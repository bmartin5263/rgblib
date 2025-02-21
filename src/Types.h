//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_TYPES_H
#define RGBLIB_TYPES_H

#include <optional>
#include <cstdint>

namespace rgb {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using byte = u8;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using milliseconds = unsigned long;
using microseconds = unsigned long;
using frame_time = unsigned long;
using pin_num = i8;
using cstring = const char*;

}

#endif //RGBLIB_TYPES_H
