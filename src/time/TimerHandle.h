//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMERHANDLE_H
#define RGBLIB_TIMERHANDLE_H

#include <memory>
#include "Handle.h"

namespace rgb {

class TimerNode;
struct HandleDeleter {
  constexpr HandleDeleter() noexcept = default;
  auto operator()(TimerNode* ptr) -> void;
};

using TimerHandle = std::unique_ptr<TimerNode, HandleDeleter>;

}

#endif //RGBLIB_TIMERHANDLE_H
