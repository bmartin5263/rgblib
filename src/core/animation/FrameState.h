//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_FRAMESTATE_H
#define RGBLIB_FRAMESTATE_H

#include "Types.h"

namespace rgb {

enum class FrameStatus {
  RUNNING, FINISHED
};

// Not every Frame type reads/writes each value here
struct FrameState {
  Timestamp elapsed{};
  u32 iteration{};

  auto reset() -> void {
    *this = {};
  }
};

}

#endif //RGBLIB_FRAMESTATE_H
