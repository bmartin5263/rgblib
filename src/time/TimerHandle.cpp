//
// Created by Brandon on 3/26/25.
//

#include "TimerHandle.h"
#include "Timer.h"

namespace rgb {

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
    release();
  }
}

TimerHandle::~TimerHandle() {
  INFO("~TimerHandle(id=%ui)", handleId);
  cancel();
}

TimerHandle::TimerHandle(TimerHandle&& rhs) noexcept {
  this->node = rhs.node;
  this->handleId = rhs.handleId;
  rhs.release();
}

TimerHandle& TimerHandle::operator=(TimerHandle&& rhs) noexcept {
  this->node = rhs.node;
  this->handleId = rhs.handleId;
  rhs.release();
  return *this;
}

auto TimerHandle::release() -> void {
  this->node = nullptr;
  this->handleId = 0;
}

}