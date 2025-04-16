//
// Created by Brandon on 3/26/25.
//

#include "TimerHandle.h"
#include "Timer.h"

namespace rgb {

auto HandleDeleter::operator()(rgb::TimerNode* ptr) -> void {
  Timer::Cancel(ptr);
}

}