//
// Created by Brandon on 3/25/25.
//

#include "Timer.h"
#include "Assertions.h"
#include "Clock.h"

namespace rgb {

Timer::Timer() {
  INFO("Initializing Timers");
}

auto Timer::SetTimeout(Duration duration, const Runnable& function) -> TimerHandle {
  return Instance().setTimeout(duration, function);
}

auto Timer::ContinuouslyFor(Duration duration, const Runnable& function) -> TimerHandle {
  return Instance().continuouslyFor(duration, [=](const auto& unused){ function(); });
}

auto Timer::ContinuouslyFor(Duration duration, const TimerFunction& function) -> TimerHandle {
  return Instance().continuouslyFor(duration, function);
}

auto Timer::ContinuouslyWhile(const Predicate& function) -> TimerHandle {
  return Instance().continuouslyWhile(function);
}

auto Timer::SetTimeout(Duration duration, const TimerFunction& function) -> TimerHandle {
  return Instance().setTimeout(duration, function);
}

auto Timer::SetImmediateTimeout(const Runnable& function) -> TimerHandle {
  return Instance().setImmediateTimeout(function);
}

auto Timer::SetImmediateTimeout(const TimerFunction& function) -> TimerHandle {
  return Instance().setImmediateTimeout(function);
}

auto Timer::setTimeout(Duration duration, const TimerFunction& function) -> TimerHandle {
  TRACE("SetTimeout()");
  auto now = Clock::Now();
  auto timer = nextTimerNode();

  timer->clean();
  timer->timerFunction = function;
  timer->cancelFunction = DoNothing;
  timer->executeAt = now + duration;
  timer->handleId = nextHandleId++;
  timer->startedAt = now;

  TRACE("Assigning Timer '%i'", timer->id);
  enqueueForAdding(timer);

  return TimerHandle { timer };
}

auto Timer::continuouslyWhile(const Predicate& function) -> TimerHandle {
  TRACE("ContinuouslyWhile()");
  auto now = Clock::Now();
  auto timer = nextTimerNode();

  timer->clean();
  timer->timerFunction = [function](TimerContext& context){
    auto doContinue = function();
    if (doContinue) {
      context.repeatIn = Duration::Immediately();
    }
  };
  timer->cancelFunction = DoNothing;
  timer->executeAt = now;
  timer->handleId = nextHandleId++;
  timer->startedAt = now;

  TRACE("Assigning Timer '%i'. startedAt=%llu, finishAt=%llu", timer->id, timer->startedAt.value, timer->finishAt.value);
  enqueueForAdding(timer);

  return TimerHandle { timer };
}

auto Timer::continuouslyFor(Duration duration, const TimerFunction& function) -> TimerHandle {
  TRACE("ContinuouslyFor()");
  auto now = Clock::Now();
  auto timer = nextTimerNode();

  timer->clean();
  timer->timerFunction = function;
  timer->cancelFunction = DoNothing;
  timer->finishAt = now + duration;
  timer->executeAt = now;
  timer->startedAt = now;
  timer->handleId = nextHandleId++;

  TRACE("Assigning Timer '%i'. startedAt=%llu, finishAt=%llu", timer->id, timer->startedAt.value, timer->finishAt.value);
  enqueueForAdding(timer);

  return TimerHandle { timer };
}

auto Timer::Cancel(TimerNode* node) -> void {
  Instance().cancel(node);
}

auto Timer::cancel(TimerNode* node) -> void {
  if (node != nullptr) {
    TRACE("Cancelling Timer '%i'", node->id);
    node->cancelled = true;
  }
}

auto Timer::ProcessTimers() -> void {
  Instance().processTimers();
}

auto Timer::processTimers() -> void {
  processAdditions();

  auto now = Clock::Now();
  while (activeHead != nullptr && activeHead->executeAt <= now) {
    auto timer = TimerNode::Pop(activeHead);
    if (timer->cancelled) {
      timer->cancelFunction();
      recycle(timer);
    }
    else {
      executeTimer(timer, now);
    }
  }
}

auto Timer::executeTimer(TimerNode* timer, Timestamp now) -> void {
  auto shouldRecycle = false;
  if (timer->isContinuous()) {
    shouldRecycle = executeContinuousTimer(timer, now);
  }
  else {
    shouldRecycle = executeRegularTimer(timer, now);
  }

  if (shouldRecycle) {
    recycle(timer);
  }
}

auto Timer::processAdditions() -> void {
  while (toAddHead != nullptr) {
    auto nodeToInsert = toAddHead;
    toAddHead = toAddHead->next;

    nodeToInsert->prev = nullptr;
    nodeToInsert->next = nullptr;

    TimerNode::Insert(activeHead, nodeToInsert);
  }
}

auto Timer::nextTimerNode() -> TimerNode* {
  if (unusedHead == nullptr) {
    reclaimNodes();
  }
  auto next = popUnused();
  ++usedCount;
  if (usedCount > maxUsedCount) {
    maxUsedCount = usedCount;
  }
  return next;
}

auto Timer::reclaimNodes() -> void {
  INFO("Reclaiming Timer Nodes");
  for (auto& timer : nodes) {
    if (timer.cancelled) {
      TimerNode::Remove(activeHead, &timer);
      timer.clean();
      TimerNode::InsertFront(unusedHead, &timer);
      --usedCount;
    }
  }
}

auto Timer::Instance() -> Timer& {
  static Timer timer;
  return timer;
}

auto Timer::activeCount() const -> uint {
  return usedCount;
}

auto Timer::ActiveCount() -> uint {
  return Instance().activeCount();
}

auto Timer::recycle(TimerNode* timer) -> void {
  TRACE("Recycling Timer '%i'", timer->id);
  timer->clean();
  TimerNode::InsertFront(unusedHead, timer);
  --usedCount;
}

auto Timer::executeRegularTimer(TimerNode* timer, Timestamp now) -> bool {
  auto context = TimerContext{};
  TRACE("Running Timer '%i'", timer->id);
  timer->timerFunction(context);
  if (context.repeatIn) {
    TRACE("Repeating Timer '%i' in '%llu'", timer->id, context.repeatIn.value().value);
    timer->repeat(now + context.repeatIn.value());
    enqueueForAdding(timer);
    return false;
  }
  else {
    return true;
  }
}

auto Timer::executeContinuousTimer(TimerNode* timer, Timestamp now) -> bool {
  auto context = TimerContext{};
  context.percentComplete = std::min(1.0f, (now - timer->startedAt).percentOf(timer->finishAt - timer->startedAt));
  timer->timerFunction(context);
  if (now < timer->finishAt) {
    timer->repeat(now);
    enqueueForAdding(timer);
    return false;
  }
  else {
    return true;
  }
}

auto Timer::setTimeout(Duration duration, const Runnable& function) -> TimerHandle {
  return setTimeout(duration, [=](const auto& unused){ function(); });
}

auto Timer::setImmediateTimeout(const Runnable& function) -> TimerHandle {
  return setTimeout(Duration::Zero(), [=](const auto& unused){ function(); });
}

auto Timer::setImmediateTimeout(const TimerFunction& function) -> TimerHandle {
  return setTimeout(Duration::Zero(), function);
}

auto Timer::MaxCount() -> uint {
  return Instance().maxCount();
}

auto Timer::maxCount() const -> uint {
  return maxUsedCount;
}

auto Timer::stopAll() -> void {
  auto current = activeHead;
  while (current != nullptr) {
    current->cancelled = true;
    current = current->next;
  }
}

auto Timer::StopAll() -> void {
  Instance().stopAll();
}

}
