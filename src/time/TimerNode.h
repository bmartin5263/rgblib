//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMERNODE_H
#define RGBLIB_TIMERNODE_H

#include "Types.h"
#include "Assertions.h"
#include "Func.h"

namespace rgb {

struct TimerContext {
  std::optional<Duration> repeatIn{};
  normal percentComplete{1.0f};
};

using TimerFunction = Consumer<TimerContext&>;

struct TimerNode {
  TimerNode* prev{};
  TimerNode* next{};
  TimerFunction timerFunction{};
  Timestamp executeAt{};
  Timestamp startedAt{};
  Timestamp finishAt{};
  uint id{};
  uint handleId{};
  bool tombstone{};

  auto clean() -> void {
    prev = nullptr;
    next = nullptr;
    timerFunction = {};
    tombstone = false;
    handleId = 0;
    startedAt = Timestamp{0};
    finishAt = Timestamp{0};
  }

  auto isContinuous() -> bool {
    return finishAt != Timestamp{0};
  }

  auto repeat(Timestamp now, Duration delta) -> void {
    tombstone = false; // User code could have set this to `true` while executing the timer function
    executeAt = now + delta;
  }

  static auto InsertFront(TimerNode*& head, TimerNode* node) {
    ASSERT(node->next == nullptr, "Next is not nullptr");
    ASSERT(node->prev == nullptr, "Prev is not nullptr");

    node->prev = nullptr;
    node->next = head;
    if (head != nullptr) {
      head->prev = node;
    }
    head = node;
  }

  static auto Pop(TimerNode*& head) -> TimerNode* {
    ASSERT(head != nullptr, "Popping from empty list");
    auto popped = head;
    ASSERT(popped->prev == nullptr, "Prev is not nullptr");

    if (head->next != nullptr) {
      head->next->prev = nullptr;
    }
    head = head->next;

    popped->next = nullptr;
    popped->prev = nullptr;

    return popped;
  }

  static auto Remove(TimerNode*& head, TimerNode* nodeToRemove) -> void {
    ASSERT(head != nullptr, "Removing from empty list");
    ASSERT(nodeToRemove != nullptr, "Removing null node");
    ASSERT(nodeToRemove != head, "Attempting to remove head without Pop()");

    if (nodeToRemove->next != nullptr) {
      nodeToRemove->next->prev = nodeToRemove->prev;
    }
    if (nodeToRemove->prev != nullptr) {
      nodeToRemove->prev->next = nodeToRemove->next;
    }
    nodeToRemove->next = nullptr;
    nodeToRemove->prev = nullptr;
  }
};

}


#endif //RGBLIB_TIMERNODE_H
