//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMERNODE_H
#define RGBLIB_TIMERNODE_H

#include <optional>
#include "Types.h"
#include "Assertions.h"
#include "PriorityNode.h"
#include "Func.h"

namespace rgb {

struct TimerContext {
  std::optional<Duration> repeatIn{};
  normal percentComplete{1.0f};
};

using TimerFunction = Consumer<TimerContext&>;

struct TimerNode : PriorityNode<TimerNode> {
  TimerFunction timerFunction{};
  Runnable cancelFunction{DoNothing};
  Timestamp executeAt{};
  Timestamp startedAt{};
  Timestamp finishAt{};
  uint id{};
  uint handleId{};
  bool cancelled{};

  auto clean() -> void {
    prev = nullptr;
    next = nullptr;
    timerFunction = {};
    cancelFunction = DoNothing;
    executeAt = Timestamp{};
    startedAt = Timestamp{};
    finishAt = Timestamp{};
    handleId = 0;
    cancelled = false;
  }

  auto isContinuous() -> bool {
    return finishAt != Timestamp{0};
  }

  auto repeat(Timestamp when) -> void {
    cancelled = false; // User code could have set this to `true` while executing the timer function
    executeAt = when;
  }

  auto operator<(const TimerNode& rhs) const -> bool {
    return executeAt < rhs.executeAt;
  }
};

}


#endif //RGBLIB_TIMERNODE_H
