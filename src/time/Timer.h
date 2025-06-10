//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMER_H
#define RGBLIB_TIMER_H

#include "Config.h"
#include "Types.h"
#include "TimerNode.h"
#include "TimerHandle.h"

namespace rgb {

class Timer {
  static constexpr auto TIMER_COUNT = 10;

public:
  static auto SetTimeout(Duration duration, const Runnable& function) -> TimerHandle;
  static auto SetTimeout(Duration duration, const TimerFunction& function) -> TimerHandle;
  static auto SetImmediateTimeout(const Runnable& function) -> TimerHandle;
  static auto SetImmediateTimeout(const TimerFunction& function) -> TimerHandle;
  static auto ContinuouslyFor(Duration duration, const Runnable& function) -> TimerHandle;
  static auto ContinuouslyFor(Duration duration, const TimerFunction& function) -> TimerHandle;

  static auto ProcessTimers() -> void;
  static auto Cancel(TimerNode* node) -> void;
  static auto Count() -> decltype(TIMER_COUNT);
  static auto Instance() -> Timer&;

private:
  TimerNode nodes[TIMER_COUNT]{};
  TimerNode* unusedHead{nullptr};
  TimerNode* toAddHead{nullptr};
  TimerNode* activeHead{nullptr};
  uint nextHandleId{1};

  auto setTimeout(Duration duration, const TimerFunction& function) -> TimerHandle;
  auto continuouslyFor(Duration duration, const TimerFunction& function) -> TimerHandle;
  auto cancel(TimerNode* node) -> void;
  auto processTimers() -> void;
  auto executeTimer(TimerNode* node, Timestamp now) -> void;
  auto nextTimerNode() -> TimerNode*;
  auto enqueueForAdding(TimerNode* node) -> void;
  auto processAdditions() -> void;
  auto reclaimNodes() -> void;
  auto count() -> decltype(TIMER_COUNT);

  Timer();
  Timer(const Timer& rhs) = default;
  Timer(Timer&& rhs) noexcept = default;
  Timer& operator=(const Timer& rhs) = default;
  Timer& operator=(Timer&& rhs) noexcept = default;
  ~Timer() = default;
};

}


#endif //RGBLIB_TIMER_H
