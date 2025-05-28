//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_TIMERNODE_H
#define RGBLIB_TIMERNODE_H

#include "Func.h"
#include "Types.h"
#include "Assertions.h"

namespace rgb {

struct TimerNode {
  TimerNode* prev{};
  TimerNode* next{};
  Runnable timerFunction{};
  Timestamp executeAt{};
  Duration timeBetweenExecutions{};
  uint repeatsRemaining{};
  bool tombstone{};

  auto clean() -> void {
    *this = {};
  }

  auto repeat(Timestamp now) -> void {
    ASSERT(repeatsRemaining > 0, "No repeats remaining");
    --repeatsRemaining;
    tombstone = false; // User code could have set this to `true` while executing the timer function
    executeAt = now + timeBetweenExecutions;
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
