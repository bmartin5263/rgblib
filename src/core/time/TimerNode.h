//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMERNODE_H
#define RGBLIB_TIMERNODE_H

#include <optional>
#include <variant>
#include "Types.h"
#include "Assertions.h"
#include "PriorityNode.h"
#include "Func.h"

namespace rgb {

struct TimerContext {
  std::optional<Duration> repeatIn{};
  normal percentComplete{1.0f};
};

using TimerFunction = Function<void(TimerContext&)>;
using TimerCallback = std::variant<Runnable, Predicate, TimerFunction>;

struct TimerNode : PriorityNode<TimerNode> {
  TimerCallback callback{};
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
    callback = {};
    cancelFunction = DoNothing;
    executeAt = Timestamp{};
    startedAt = Timestamp{};
    finishAt = Timestamp{};
    handleId = 0;
    cancelled = false;
  }

  auto execute(TimerContext& context) const -> void {
    if (auto runnable = std::get_if<Runnable>(&callback)) {
      (*runnable)();
    }
    else if (auto predicate = std::get_if<Predicate>(&callback)) {
      if ((*predicate)()) {
        context.repeatIn = Duration::Immediately();
      }
    }
    else if (auto timerFunction = std::get_if<TimerFunction>(&callback)) {
      (*timerFunction)(context);
    }
    else {
      FAIL("Unhandled TimerContext callback type");
    }
  }

  auto isContinuous() const -> bool {
    return finishAt != Timestamp{0};
  }

  auto isTombstone() const -> bool {
    return cancelled;
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
