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
public:
  static auto SetTimeout(Duration duration, const rgb::TimerFunction& function) -> TimerHandle;
  static auto SetInterval(Duration duration, uint times, const rgb::TimerFunction& function) -> TimerHandle;
  static auto ProcessTimers() -> void;
  static auto Cancel(TimerNode* node) -> void;
  static auto Count() -> decltype(config::TIMERS);
  static auto Instance() -> Timer&;

private:
  TimerNode nodes[rgb::config::TIMERS] {};
  TimerNode* unusedHead{};
  TimerNode* toAddHead{nullptr};
  TimerNode* activeHead{nullptr};


  Timer();
  auto setTimeout(Duration duration, uint intervals, const rgb::TimerFunction& function) -> TimerHandle;
  auto cancel(TimerNode* node) -> void;
  auto processTimers() -> void;
  auto executeTimer(TimerNode* node, Timestamp now) -> void;
  auto nextTimerNode() -> TimerNode*;
  auto enqueueForAdding(TimerNode* node) -> void;
  auto processAdditions() -> void;
  auto reclaimNodes() -> void;
  auto count() -> decltype(config::TIMERS);
};

}


#endif //RGBLIB_TIMER_H
