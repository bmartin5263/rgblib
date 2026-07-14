//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMER_H
#define RGBLIB_TIMER_H

#include "Types.h"
#include "PriorityNodePool.h"
#include "TimerNode.h"
#include "TimerHandle.h"

namespace rgb {

class Timer : public PriorityNodePool<TimerNode, 10> {
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
  static auto Instance() -> Timer&;

  auto setTimeout(Duration duration, const Runnable& function) -> TimerHandle;
  auto setTimeout(Duration duration, const TimerFunction& function) -> TimerHandle;
  auto setImmediateTimeout(const Runnable& function) -> TimerHandle;
  auto setImmediateTimeout(const TimerFunction& function) -> TimerHandle;
  auto continuouslyFor(Duration duration, const TimerFunction& function) -> TimerHandle;
  auto continuouslyWhile(const Predicate& function) -> TimerHandle;
  auto activeCount() const -> uint;
  auto maxCount() const -> uint;
  auto cancel(TimerNode* node) -> void;
  auto processTimers() -> void;

  Timer();
  Timer(const Timer& rhs) = default;
  Timer(Timer&& rhs) noexcept = default;
  Timer& operator=(const Timer& rhs) = default;
  Timer& operator=(Timer&& rhs) noexcept = default;
  ~Timer() = default;

private:
  uint usedCount{0};
  uint maxUsedCount{0};

  auto executeTimer(TimerNode* node, Timestamp now) -> void;
  auto nextTimerNode() -> TimerNode*;
  auto processAdditions() -> void;
  auto reclaimNodes() -> void;
  auto stopAll() -> void;
  auto recycle(TimerNode* timer) -> void;
  auto executeRegularTimer(TimerNode* timer, Timestamp now) -> bool;
  auto executeContinuousTimer(TimerNode* timer, Timestamp now) -> bool;
};

}


#endif //RGBLIB_TIMER_H
