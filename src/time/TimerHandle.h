//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMERHANDLE_H
#define RGBLIB_TIMERHANDLE_H

#include <memory>
#include "Handle.h"
#include "Func.h"

namespace rgb {

class TimerNode;

class TimerHandle {
public:
  TimerHandle();
  explicit TimerHandle(TimerNode* node);
  TimerHandle(const TimerHandle& rhs) = delete;
  TimerHandle(TimerHandle&& rhs) noexcept;
  TimerHandle& operator=(const TimerHandle& rhs) = delete;
  TimerHandle& operator=(TimerHandle&& rhs) noexcept;
  ~TimerHandle();

  // Release ownership of the timer without canceling it
  auto detach() -> void;

  // Release ownership and cancel the timer
  auto cancel() -> void;

  // Callback for when the timer is manually cancelled
  auto onCancel(const Runnable& function) -> TimerHandle&;

  auto isScheduled() -> bool;

private:
  uint handleId;
  TimerNode* node;
};

}

#endif //RGBLIB_TIMERHANDLE_H
