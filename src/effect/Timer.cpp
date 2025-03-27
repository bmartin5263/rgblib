//
// Created by Brandon on 3/25/25.
//

#include "Timer.h"
#include "Assertions.h"
#include "Clock.h"

namespace rgb {

Timer::Timer() {
  INFO("Initializing Timers");
  for (int i = 0; i < config::TIMERS; ++i) {
    auto& current = nodes[i];
    if (i > 0) {
      current.prev = &nodes[i - 1];
    }
    if (i < config::TIMERS - 1) {
      current.prev = &nodes[i + 1];
    }
  }
  unusedHead = &nodes[0];
}

auto Timer::SetTimeout(Duration duration, const rgb::TimerFunction& function) -> TimerHandle {
  return Instance().setTimeout(duration, 1, function);
}

auto Timer::SetInterval(rgb::Duration duration, uint times, const rgb::TimerFunction& function) -> TimerHandle {
  if (times == 0) {
    return TimerHandle {};
  }
  return Instance().setTimeout(duration, times - 1, function);
}

auto Timer::setTimeout(Duration duration, uint repeatCount, const rgb::TimerFunction& function) -> TimerHandle {
  auto time = Clock::Micro();
  auto timer = nextTimerNode();

  timer->clean();
  timer->timerFunction = function;
  timer->executeAt = time + duration.value;
  timer->repeatsRemaining = repeatCount;
  timer->timeBetweenExecutions = duration;

  TimerNode::InsertFront(toAddHead, timer);

  return TimerHandle { timer };
}

auto Timer::Cancel(TimerNode* node) -> void {
  Instance().cancel(node);
}

auto Timer::cancel(TimerNode* node) -> void {
  ASSERT(node != nullptr, "TimerNode is null");
  node->tombstone = true;
}

auto Timer::enqueueForAdding(TimerNode* node) -> void {
  TimerNode::InsertFront(toAddHead, node);
}

auto Timer::ProcessTimers() -> void {
  Instance().processTimers();
}

auto Timer::processTimers() -> void {
  processAdditions();

  auto now = Clock::Micro();
  while (activeHead != nullptr && activeHead->executeAt <= now) {
    auto timer = TimerNode::Pop(activeHead);
    if (timer->tombstone) {
      TimerNode::InsertFront(unusedHead, timer);
      continue;
    }

    executeTimer(timer);

    if (timer->repeatsRemaining > 0) {
      timer->repeat(now);
      enqueueForAdding(timer);
    }
    else {
      TimerNode::InsertFront(unusedHead, timer);
    }
  }
}

auto Timer::executeTimer(TimerNode* node) -> void {
  node->timerFunction();
}

auto Timer::processAdditions() -> void {
  while (toAddHead != nullptr) {
    auto nodeToInsert = toAddHead;
    toAddHead = toAddHead->next;

    if (activeHead == nullptr || nodeToInsert->executeAt < activeHead->executeAt) {
      TimerNode::InsertFront(activeHead, nodeToInsert);
      continue;
    }

    auto current = activeHead;
    while (current->next != nullptr && current->next->executeAt < nodeToInsert->executeAt) {
      current = current->next;
    }

    // todo current->next->executeAt >= nodeToInsert->executeAt
    nodeToInsert->prev = current;
    nodeToInsert->next = current->next;
    if (current->next != nullptr) {
      current->next->prev = nodeToInsert;
    }
  }
}

auto Timer::nextTimerNode() -> TimerNode* {
  if (unusedHead == nullptr) {
    INFO("Reclaiming Timer Nodes");
    reclaimNodes();
    ASSERT(unusedHead != nullptr, "No more timer nodes available");
  }
  return TimerNode::Pop(unusedHead);
}

auto Timer::reclaimNodes() -> void {
  for (auto& node : nodes) {
    if (node.tombstone) {
      TimerNode::Remove(activeHead, &node);
      node.tombstone = false;
      TimerNode::InsertFront(unusedHead, &node);
    }
  }
}

auto Timer::Instance() -> Timer& {
  static Timer timer;
  return timer;
}

auto Timer::Count() -> decltype(config::TIMERS) {
  return Instance().count();
}

auto Timer::count() -> decltype(config::TIMERS) {
  auto num = static_cast<decltype(config::TIMERS)>(0);
  auto current = activeHead;
  while (current != nullptr) {
    if (!current->tombstone) {
      ++num;
    }
    current = current->next;
  }
  return num;
}

}
