//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMERNODE_H
#define RGBLIB_TIMERNODE_H

#include <functional>
#include "Types.h"
#include "Assertions.h"

namespace rgb {

using TimerFunction = std::function<void()>;

struct TimerNode {
  TimerNode* prev{};
  TimerNode* next{};
  TimerFunction timerFunction{};
  microseconds executeAt{};
  Duration timeBetweenExecutions{};
  uint repeatsRemaining{};
  bool tombstone{};

  auto clean() -> void {
    memset(this, 0, sizeof(TimerNode));
  }

  auto isReady(microseconds time) -> bool {
    return executeAt <= time;
  }

  auto repeat(microseconds now) -> void {
    ASSERT(repeatsRemaining > 0, "No repeats remaining");
    --repeatsRemaining;
    executeAt = now + timeBetweenExecutions.value;
  }

  static auto InsertFront(TimerNode*& head, TimerNode* node) {
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
    Remove(head, head);
    return popped;
  }

  static auto Remove(TimerNode*& head, TimerNode* nodeToRemove) -> void {
    ASSERT(head != nullptr, "Removing from empty list");
    ASSERT(nodeToRemove != nullptr, "Removing null node");
    if (nodeToRemove == head) {
      head = head->next;
      if (head != nullptr) {
        head->prev = nullptr;
      }
      nodeToRemove->next = nullptr;
      return;
    }

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
