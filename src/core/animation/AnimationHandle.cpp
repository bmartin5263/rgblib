//
// Created by Brandon on 3/26/25.
//

#include "AnimationHandle.h"
#include "AnimationNode.h"

namespace rgb {

AnimationHandle::AnimationHandle(AnimationNode* node): handleId(node->handleId), node(node) {

}

AnimationHandle::AnimationHandle(): handleId(0), node(nullptr) {

}

auto AnimationHandle::stop() -> void {
  if (node != nullptr) {
    TRACE("AnimationHandle(id=%ui)::cancel()", handleId);
    if (node->handleId == handleId) {
      node->stopped = true;
    }
    detach();
  }
}

AnimationHandle::~AnimationHandle() {
  TRACE("~AnimationHandle(id=%u)", handleId);
  stop();
}

AnimationHandle::AnimationHandle(AnimationHandle&& rhs) noexcept {
  this->node = rhs.node;
  this->handleId = rhs.handleId;
  rhs.detach();
}

AnimationHandle& AnimationHandle::operator=(AnimationHandle&& rhs) noexcept {
  stop();
  this->node = rhs.node;
  this->handleId = rhs.handleId;
  rhs.detach();
  return *this;
}

auto AnimationHandle::detach() -> void {
  this->node = nullptr;
  this->handleId = 0;
}

auto AnimationHandle::isRunning() const -> bool {
  return node != nullptr
      && node->handleId == handleId
      && !node->stopped;
}

}