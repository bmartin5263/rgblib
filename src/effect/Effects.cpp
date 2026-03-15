//
// Created by Brandon on 3/25/25.
//

#include "Effects.h"
#include "Assertions.h"
#include "Clock.h"

namespace rgb {

Effects::Effects() {
  INFO("Initializing Effects");
  for (int i = 0; i < EFFECT_COUNT; ++i) {
    auto& current = nodes[i];
    current.id = i;
    if (i > 0) {
      current.prev = &nodes[i - 1];
    }
    else {
      current.prev = nullptr;
    }
    if (i < EFFECT_COUNT - 1) {
      current.next = &nodes[i + 1];
    }
    else {
      current.next = nullptr;
    }
  }
  for (int i = 0; i < EFFECT_COUNT; ++i) {
    ASSERT(nodes[i].id == i, "Id invalid");
    if (i != 0) {
      ASSERT(nodes[i].prev == &nodes[i - 1], "Prev Mismatch");
    }
    if (i != EFFECT_COUNT - 1) {
      ASSERT(nodes[i].next == &nodes[i + 1], "Next Mismatch");
    }
  }
  unusedHead = &nodes[0];
  ASSERT(unusedHead != nullptr, "Failed to initialize Effects");
  ASSERT(nodes[0].prev == nullptr, "Head invalid");
  ASSERT(nodes[EFFECT_COUNT - 1].next == nullptr, "Tail invalid");
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

  EffectNode::InsertFront(toAddHead, effectNode);

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

  EffectNode::InsertFront(toAddHead, effectNode);

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

    if (activeHead == nullptr || nodeToInsert->priority < activeHead->priority) {
      EffectNode::InsertFront(activeHead, nodeToInsert);
      TRACE(
        "Activated Effect '%i'. To Add Effects: %i. Active Effects %i. Unused Effects %i",
        nodeToInsert->id, EffectNode::Size(toAddHead), EffectNode::Size(activeHead), EffectNode::Size(unusedHead));
      continue;
    }

    auto current = activeHead;
    while (current->next != nullptr && current->next->priority < nodeToInsert->priority) {
      current = current->next;
    }

    // todo current->next->priority >= nodeToInsert->priority
    ASSERT(nodeToInsert->priority >= current->priority, "Node in wrong position");

    nodeToInsert->prev = current;
    nodeToInsert->next = current->next;
    if (current->next != nullptr) {
      current->next->prev = nodeToInsert;
    }
    current->next = nodeToInsert;

    TRACE(
      "Activated Effect '%i'. To Add Effects: %i. Active Effects %i. Unused Effects %i",
      nodeToInsert->id, EffectNode::Size(toAddHead), EffectNode::Size(activeHead), EffectNode::Size(unusedHead));
  }
}

auto Effects::nextEffectNode() -> EffectNode* {
  if (unusedHead == nullptr) {
    reclaimNodes();
    ASSERT_C(unusedHead != nullptr, "No more timer nodes available", Color::WHITE());
  }
  auto next = EffectNode::Pop(unusedHead);
  ASSERT(next->next == nullptr, "Next is not a nullptr");
  ASSERT(next->prev == nullptr, "Prev is not a nullptr");
  return next;
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
