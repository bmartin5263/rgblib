//
// Created by Brandon on 3/26/25.
//

#include "TimerHandle.h"
#include "Timer.h"

namespace rgb {

auto HandleDeleter::operator()(rgb::TimerNode* ptr) -> void {
  INFO("HandleDeleter()");
  Timer::Cancel(ptr);
}

TimerHandle::TimerHandle(TimerNode* node): handleId(node->handleId), node(node) {

}

TimerHandle::TimerHandle(): handleId(0), node(nullptr) {

}

auto TimerHandle::cancel() -> void {
  INFO("TimerHandle(id=%ui)::cancel()", handleId);
  if (node != nullptr) {
    if (node->handleId == handleId) {
      Timer::Cancel(node);
    }
    node = nullptr;
  }
}

TimerHandle::~TimerHandle() {
  INFO("~TimerHandle(id=%ui)", handleId);
  cancel();
}

TimerHandle::TimerHandle(TimerHandle&& rhs) noexcept {
  this->node = rhs.node;
  this->handleId = rhs.handleId;
  rhs.node = nullptr;
  rhs.handleId = 0;
}

TimerHandle& TimerHandle::operator=(TimerHandle&& rhs) noexcept {
  this->node = rhs.node;
  this->handleId = rhs.handleId;
  rhs.node = nullptr;
  rhs.handleId = 0;
  return *this;
}


}