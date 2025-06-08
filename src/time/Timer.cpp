//
// Created by Brandon on 3/25/25.
//

#include "Timer.h"
#include "Assertions.h"
#include "Clock.h"

namespace rgb {

Timer::Timer() {
  INFO("Initializing Timers");
  for (int i = 0; i < TIMER_COUNT; ++i) {
    auto& current = nodes[i];
    if (i > 0) {
      current.prev = &nodes[i - 1];
    }
    if (i < TIMER_COUNT - 1) {
      current.prev = &nodes[i + 1];
    }
  }
  unusedHead = &nodes[0];
  ASSERT(unusedHead != nullptr, "Failed to initialize Timers");
}

auto Timer::SetTimeout(Duration duration, const Runnable& function) -> TimerHandle {
  return Instance().setTimeout(duration, 0, [=](){ function(); return false; });
}

auto Timer::SetInterval(rgb::Duration duration, uint times, const Runnable& function) -> TimerHandle {
  if (times == 0) {
    return TimerHandle {};
  }
  return Instance().setTimeout(duration, times - 1, [=](){ function(); return false; });
}

auto Timer::SetTimeout(Duration duration, const TimerFunction& function) -> TimerHandle {
  return Instance().setTimeout(duration, 0, function);
}

auto Timer::SetInterval(rgb::Duration duration, uint times, const TimerFunction& function) -> TimerHandle {
  if (times == 0) {
    return TimerHandle {};
  }
  return Instance().setTimeout(duration, times - 1, function);
}

auto Timer::setTimeout(Duration duration, uint repeatCount, const TimerFunction& function) -> TimerHandle {
  INFO("SetTimeout()");
  auto time = Clock::Now();
  auto timer = nextTimerNode();

  timer->clean();
  timer->timerFunction = function;
  timer->executeAt = time + duration;
  timer->repeatsRemaining = repeatCount;
  timer->timeBetweenExecutions = duration;

  TimerNode::InsertFront(toAddHead, timer);

  return TimerHandle { timer };
}

auto Timer::Cancel(TimerNode* node) -> void {
  Instance().cancel(node);
}

auto Timer::cancel(TimerNode* node) -> void {
  if (node != nullptr) {
    INFO("Cancelling Timer");
    node->tombstone = true;
  }
}

auto Timer::enqueueForAdding(TimerNode* node) -> void {
  TimerNode::InsertFront(toAddHead, node);
}

auto Timer::ProcessTimers() -> void {
  Instance().processTimers();
}

auto Timer::processTimers() -> void {
  processAdditions();

  auto now = Clock::Now();
  while (activeHead != nullptr && activeHead->executeAt <= now) {
    auto timer = TimerNode::Pop(activeHead);
    if (timer->tombstone) {
      TimerNode::InsertFront(unusedHead, timer);
      continue;
    }
    executeTimer(timer, now);
  }
}

auto Timer::executeTimer(TimerNode* timer, Timestamp now) -> void {
  INFO("Start Executing Timer");
  auto repeat = timer->timerFunction();
  INFO("Finish Executing Timer");
  if (repeat || timer->repeatsRemaining > 0) {
    INFO("Repeating Timer");
    timer->repeat(now);
    enqueueForAdding(timer);
  }
  else {
    INFO("Trashing Timer");
    TimerNode::InsertFront(unusedHead, timer);
  }
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

auto Timer::Count() -> decltype(TIMER_COUNT) {
  return Instance().count();
}

auto Timer::count() -> decltype(TIMER_COUNT) {
  auto num = static_cast<decltype(TIMER_COUNT)>(0);
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
