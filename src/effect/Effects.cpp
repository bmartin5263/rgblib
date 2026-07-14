//
// Created by Brandon on 3/25/25.
//

#include "Effects.h"
#include "Assertions.h"
#include "Clock.h"

namespace rgb {

Effects::Effects() {
  INFO("Initializing Effects");
}

auto Effects::Initialize() -> void {
  Instance().initialize();
}

auto Effects::initialize() -> void {
  startTime = Clock::Now();
}

auto Effects::Start(Effect& effect, PixelList& pixels) -> EffectHandle {
  return Instance().start(effect, pixels);
}

auto Effects::start(Effect& effect, PixelList& pixels) -> EffectHandle {
  TRACE("start()");
  auto effectNode = nextEffectNode();
  ASSERT(effectNode->next == nullptr, "EffectNode.Next is not nullptr");
  ASSERT(effectNode->prev == nullptr, "EffectNode.Prev is not nullptr");

  effectNode->clean();
  effectNode->pixels = &pixels;
  effectNode->effect = &effect;
  effectNode->priority = 0;
  effectNode->handleId = nextHandleId++;

  enqueueForAdding(effectNode);

  INFO(
    "Assigning Effect '%i'. To Add Effects: %i. Active Effects %i. Unused Effects %i",
    effectNode->id, EffectNode::Size(toAddHead), EffectNode::Size(activeHead), EffectNode::Size(unusedHead));

  return EffectHandle { effectNode };
}

auto Effects::Start(Effect& effect, ManyPixelLists pixels) -> EffectHandle {
  return Instance().start(effect, pixels);
}

auto Effects::start(Effect& effect, ManyPixelLists pixels) -> EffectHandle {
  TRACE("start()");
  auto effectNode = nextEffectNode();
  ASSERT(effectNode->next == nullptr, "EffectNode.Next is not nullptr");
  ASSERT(effectNode->prev == nullptr, "EffectNode.Prev is not nullptr");

  effectNode->clean();
  effectNode->pixels = pixels;
  effectNode->effect = &effect;
  effectNode->priority = 0;
  effectNode->handleId = nextHandleId++;

  enqueueForAdding(effectNode);

  INFO(
    "Assigning Effect '%i'. To Add Effects: %i. Active Effects %i. Unused Effects %i",
    effectNode->id, EffectNode::Size(toAddHead), EffectNode::Size(activeHead), EffectNode::Size(unusedHead));

  return EffectHandle { effectNode };
}

auto Effects::Update() -> void {
  Instance().update();
}

auto Effects::update() -> void {
  if (startTime.isZero()) {
    startTime = Clock::Now();
  }
  auto now = Clock::Now() - startTime;
  processAdditions(now);

  auto effect = activeHead;
  while (effect != nullptr) {
    if (effect->stopping) {
      effect = recycle(effect);
    }
    else {
      effect->update(now);
      effect = effect->next;
    }
  }
}

auto Effects::Draw() -> void {
  Instance().draw();
}

auto Effects::draw() -> void {
  if (startTime.isZero()) {
    startTime = Clock::Now();
  }
  auto now = Clock::Now() - startTime;
  auto effect = activeHead;
  while (effect != nullptr) {
    effect->draw(now);
    effect = effect->next;
  }
}

auto Effects::processAdditions(Timestamp now) -> void {
  while (toAddHead != nullptr) {
    auto nodeToInsert = toAddHead;
    nodeToInsert->start(now);
    toAddHead = toAddHead->next;

    nodeToInsert->prev = nullptr;
    nodeToInsert->next = nullptr;

    EffectNode::Insert(activeHead, nodeToInsert);

    TRACE(
      "Activated Effect '%i'. To Add Effects: %i. Active Effects %i. Unused Effects %i",
      nodeToInsert->id, EffectNode::Size(toAddHead), EffectNode::Size(activeHead), EffectNode::Size(unusedHead));
  }
}

auto Effects::nextEffectNode() -> EffectNode* {
  if (unusedHead == nullptr) {
    reclaimNodes();
  }
  return popUnused();
}

auto Effects::reclaimNodes() -> void {
  INFO("Reclaiming Effects Nodes");
  for (auto& node : nodes) {
    if (node.stopping) {
      EffectNode::Remove(activeHead, &node);
      node.stopping = false;
      EffectNode::InsertFront(unusedHead, &node);
    }
  }
}

auto Effects::Instance() -> Effects& {
  static Effects timer;
  return timer;
}

auto Effects::activeCount() -> uint {
  auto num = 0;
  auto current = activeHead;
  while (current != nullptr) {
    if (!current->stopping) {
      ++num;
    }
    current = current->next;
  }
  return num;
}

auto Effects::ActiveCount() -> uint {
  return Instance().activeCount();
}

auto Effects::recycle(EffectNode* effect) -> EffectNode* {
  auto next = effect->next;
  TRACE("Head = %p, Next = %p, ToRecycle = %p", activeHead, next, effect);
  EffectNode::Remove(activeHead, effect);
  effect->clean();
  TRACE("Head = %p, Next = %p, ToRecycle = %p", activeHead, next, effect);
  EffectNode::InsertFront(unusedHead, effect);
  TRACE(
    "Recycled Effect '%i'. To Add Effects: %i. Active Effects %i. Unused Effects %i",
    effect->id, EffectNode::Size(toAddHead), EffectNode::Size(activeHead), EffectNode::Size(unusedHead));
  TRACE("Head = %p, Next = %p, ToRecycle = %p", activeHead, next, effect);
  return next;
}

auto Effects::Stop(Effect& effect) -> void {
  Instance().stop(effect);
}

auto Effects::stop(Effect& effect) -> void {
  auto current = activeHead;
  while (current != nullptr) {
    if (current->effect == &effect) {
      current->stopping = true;
    }
    current = current->next;
  }
}

auto Effects::stopAll() -> void {
  auto current = activeHead;
  while (current != nullptr) {
    current->stopping = true;
    current = current->next;
  }
}

auto Effects::StopAll() -> void {
  Instance().stopAll();
}


}
