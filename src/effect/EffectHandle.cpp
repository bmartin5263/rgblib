//
// Created by Brandon on 3/26/25.
//

#include "EffectHandle.h"
#include "EffectNode.h"

namespace rgb {

EffectHandle::EffectHandle(EffectNode* node): handleId(node->handleId), node(node) {

}

EffectHandle::EffectHandle(): handleId(0), node(nullptr) {

}

auto EffectHandle::stop() -> void {
  if (node != nullptr) {
    TRACE("EffectHandle(id=%ui)::cancel()", handleId);
    if (node->handleId == handleId) {
      node->stopping = true;
    }
    detach();
  }
}

EffectHandle::~EffectHandle() {
  TRACE("~EffectHandle(id=%u)", handleId);
  stop();
}

EffectHandle::EffectHandle(EffectHandle&& rhs) noexcept {
  stop();
  this->node = rhs.node;
  this->handleId = rhs.handleId;
  rhs.detach();
}

EffectHandle& EffectHandle::operator=(EffectHandle&& rhs) noexcept {
  stop();
  this->node = rhs.node;
  this->handleId = rhs.handleId;
  rhs.detach();
  return *this;
}

auto EffectHandle::detach() -> void {
  this->node = nullptr;
  this->handleId = 0;
}

auto EffectHandle::isRunning() -> bool {
  return node != nullptr
      && node->handleId == handleId
      && !node->stopping;
}

}