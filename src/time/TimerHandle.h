//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMERHANDLE_H
#define RGBLIB_TIMERHANDLE_H

#include <memory>
#include "Handle.h"

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

  auto cancel() -> void;

private:
  uint handleId;
  TimerNode* node;
};

}

#endif //RGBLIB_TIMERHANDLE_H
