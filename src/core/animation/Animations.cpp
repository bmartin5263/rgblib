//
// Created by Brandon on 3/25/25.
//

#include "Animations.h"
#include "Animation.h"
#include "Assertions.h"
#include "Clock.h"

namespace rgb {

Animations::Animations() {
  INFO("Initializing Animations");
}

auto Animations::Initialize() -> void {
  Instance().initialize();
}

auto Animations::initialize() -> void {
  startTime = Clock::Now();
}
auto Animations::Start(Animation& animation, bool loop) -> AnimationHandle {
  return Instance().start(animation, loop);
}

auto Animations::start(Animation& animation, bool loop) -> AnimationHandle {
  auto animationNode = activate();
  if (animationNode == nullptr) {
    ERROR("Failed to allocate Animation");
    return AnimationHandle{};
  }

  animationNode->animation = &animation;
  animationNode->priority = 0;
  animationNode->loop = loop;

  INFO(
    "Assigning Animation '%i'. To Add Animations: %i. Active Animations %i. Unused Animations %i",
    animationNode->id, AnimationNode::Size(pInsertionQueueHead), AnimationNode::Size(pActiveHead), AnimationNode::Size(pInactiveHead));

  return AnimationHandle { animationNode };
}

auto Animations::Update() -> void {
  Instance().update();
}

auto Animations::update() -> void {
  if (startTime.isZero()) {
    startTime = Clock::Now();
  }
  auto now = Clock::Now() - startTime;
  processAdditions(now);

  auto animation = pActiveHead;
  while (animation != nullptr) {
    auto next = animation->next;
    if (animation->stopped) {
      AnimationNode::Remove(pActiveHead, animation);
      release(animation);
    }
    else if (!animation->update(now)) {
      AnimationNode::Remove(pActiveHead, animation);
      if (animation->loop) {
        recycle(animation);
      }
      else {
        release(animation);
      }
    }
    animation = next;
  }
}

auto Animations::processAdditions(Timestamp now) -> void {
  while (pInsertionQueueHead != nullptr) {
    auto nodeToInsert = pInsertionQueueHead;
    nodeToInsert->start(now);
    pInsertionQueueHead = pInsertionQueueHead->next;

    nodeToInsert->prev = nullptr;
    nodeToInsert->next = nullptr;

    AnimationNode::Insert(pActiveHead, nodeToInsert);
  }
}

auto Animations::Instance() -> Animations& {
  static Animations timer;
  return timer;
}

auto Animations::ActiveCount() -> uint {
  return Instance().activeCount();
}

auto Animations::PeakCount() -> uint {
  return Instance().peakCount();
}

auto Animations::Stop(Animation& animation) -> void {
  Instance().stop(animation);
}

auto Animations::stop(Animation& animation) -> void {
  auto current = pActiveHead;
  while (current != nullptr) {
    if (current->animation == &animation) {
      current->stopped = true;
    }
    current = current->next;
  }
  current = pInsertionQueueHead;
  while (current != nullptr) {
    if (current->animation == &animation) {
      current->stopped = true;
    }
    current = current->next;
  }
}

auto Animations::stopAll() -> void {
  auto current = pActiveHead;
  while (current != nullptr) {
    current->stopped = true;
    current = current->next;
  }
  current = pInsertionQueueHead;
  while (current != nullptr) {
    current->stopped = true;
    current = current->next;
  }
}

auto Animations::StopAll() -> void {
  Instance().stopAll();
}


}
