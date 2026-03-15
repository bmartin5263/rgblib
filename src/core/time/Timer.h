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
  [[nodiscard]]
  static auto SetTimeout(Duration duration, const Runnable& function) -> TimerHandle;
  [[nodiscard]]
  static auto SetTimeout(Duration duration, const TimerFunction& function) -> TimerHandle;
  [[nodiscard]]
  static auto SetImmediateTimeout(const Runnable& function) -> TimerHandle;
  [[nodiscard]]
  static auto SetImmediateTimeout(const TimerFunction& function) -> TimerHandle;
  [[nodiscard]]
  static auto ContinuouslyFor(Duration duration, const Runnable& function) -> TimerHandle;
  [[nodiscard]]
  static auto ContinuouslyFor(Duration duration, const TimerFunction& function) -> TimerHandle;
  [[nodiscard]]
  static auto ContinuouslyWhile(const Predicate& function) -> TimerHandle;

  static auto ProcessTimers() -> void;
  static auto Cancel(TimerNode* node) -> void;
  static auto ActiveCount() -> uint;
  static auto StopAll() -> void;
  static auto MaxCount() -> uint;
  static constexpr auto TotalCount() -> uint { return TIMER_COUNT; }
  static auto Instance() -> Timer&;

  auto setTimeout(Duration duration, const Runnable& function) -> TimerHandle;
  auto setTimeout(Duration duration, const TimerFunction& function) -> TimerHandle;
  auto setImmediateTimeout(const Runnable& function) -> TimerHandle;
  auto setImmediateTimeout(const TimerFunction& function) -> TimerHandle;
  auto continuouslyFor(Duration duration, const TimerFunction& function) -> TimerHandle;
  auto continuouslyWhile(const Predicate& function) -> TimerHandle;
  auto activeCount() -> uint;
  auto maxCount() -> uint;
  auto cancel(TimerNode* node) -> void;
  auto processTimers() -> void;

  Timer();
  Timer(const Timer& rhs) = default;
  Timer(Timer&& rhs) noexcept = default;
  Timer& operator=(const Timer& rhs) = default;
  Timer& operator=(Timer&& rhs) noexcept = default;
  ~Timer() = default;

private:
  TimerNode nodes[TIMER_COUNT]{};
  TimerNode* unusedHead{nullptr};
  TimerNode* toAddHead{nullptr};
  TimerNode* activeHead{nullptr};
  uint nextHandleId{1};

  auto executeTimer(TimerNode* node, Timestamp now) -> void;
  auto nextTimerNode() -> TimerNode*;
  auto enqueueForAdding(TimerNode* node) -> void;
  auto processAdditions() -> void;
  auto reclaimNodes() -> void;
  auto stopAll() -> void;
  auto recycle(TimerNode* timer) -> void;
  auto executeRegularTimer(TimerNode* timer, Timestamp now) -> bool;
  auto executeContinuousTimer(TimerNode* timer, Timestamp now) -> bool;
};

}


#endif //RGBLIB_TIMER_H
