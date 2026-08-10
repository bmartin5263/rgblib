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
  auto effectNode = activate();
  if (effectNode == nullptr) {
    ERROR("Failed to allocate Effect");
    return EffectHandle{};
  }

  effectNode->pixels = &pixels;
  effectNode->effect = &effect;
  effectNode->priority = 0;

  INFO(
    "Assigning Effect '%i'. To Add Effects: %i. Active Effects %i. Unused Effects %i",
    effectNode->id, EffectNode::Size(pInsertionQueueHead), EffectNode::Size(pActiveHead), EffectNode::Size(pInactiveHead));

  return EffectHandle { effectNode };
}

auto Effects::Start(Effect& effect, ManyPixelLists pixels) -> EffectHandle {
  return Instance().start(effect, pixels);
}

auto Effects::start(Effect& effect, ManyPixelLists pixels) -> EffectHandle {
  auto effectNode = activate();
  if (effectNode == nullptr) {
    ERROR("Failed to allocate Effect");
    return EffectHandle{};
  }

  effectNode->pixels = pixels;
  effectNode->effect = &effect;
  effectNode->priority = 0;

  INFO(
    "Assigning Effect '%i'. To Add Effects: %i. Active Effects %i. Unused Effects %i",
    effectNode->id, EffectNode::Size(pInsertionQueueHead), EffectNode::Size(pActiveHead), EffectNode::Size(pInactiveHead));

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

  auto effect = pActiveHead;
  while (effect != nullptr) {
    if (effect->stopped) {
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
  auto effect = pActiveHead;
  while (effect != nullptr) {
    effect->draw(now);
    effect = effect->next;
  }
}

auto Effects::processAdditions(Timestamp now) -> void {
  while (pInsertionQueueHead != nullptr) {
    auto nodeToInsert = pInsertionQueueHead;
    nodeToInsert->start(now);
    pInsertionQueueHead = pInsertionQueueHead->next;

    nodeToInsert->prev = nullptr;
    nodeToInsert->next = nullptr;

    EffectNode::Insert(pActiveHead, nodeToInsert);
  }
}

auto Effects::Instance() -> Effects& {
  static Effects timer;
  return timer;
}

auto Effects::ActiveCount() -> uint {
  return Instance().activeCount();
}

auto Effects::PeakCount() -> uint {
  return Instance().peakCount();
}

auto Effects::recycle(EffectNode* effect) -> EffectNode* {
  auto next = effect->next;
  TRACE("Head = %p, Next = %p, ToRecycle = %p", activeHead, next, effect);
  EffectNode::Remove(pActiveHead, effect);
  effect->clean();
  TRACE("Head = %p, Next = %p, ToRecycle = %p", activeHead, next, effect);
  EffectNode::InsertFront(pInactiveHead, effect);
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
  auto current = pActiveHead;
  while (current != nullptr) {
    if (current->effect == &effect) {
      current->stopped = true;
    }
    current = current->next;
  }
}

auto Effects::stopAll() -> void {
  auto current = pActiveHead;
  while (current != nullptr) {
    current->stopped = true;
    current = current->next;
  }
}

auto Effects::StopAll() -> void {
  Instance().stopAll();
}


}
