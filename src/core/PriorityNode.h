//
// Created by Brandon on 6/21/26.
//

#ifndef RGBLIB_PRIORITYNODE_H
#define RGBLIB_PRIORITYNODE_H

#include "Types.h"
#include "Assertions.h"

namespace rgb {
/**
 * @tparam Node Must implement operator <
 */
template<typename Node>
struct PriorityNode {
  Node* prev{};
  Node* next{};

  static auto Size(const Node* head) -> uint {
    auto result = 0u;
    while (head != nullptr) {
      ++result;
      head = head->next;
    }
    return result;
  }

  static auto InsertFront(Node*& head, Node* node) -> void {
    ASSERT(node->next == nullptr, "Next is not nullptr");
    ASSERT(node->prev == nullptr, "Prev is not nullptr");

    node->prev = nullptr;
    node->next = head;
    if (head != nullptr) {
      head->prev = node;
    }
    head = node;
  }

  static auto Insert(Node*& head, Node* node) -> void {
    ASSERT(node->next == nullptr, "Next is not nullptr");
    ASSERT(node->prev == nullptr, "Prev is not nullptr");

    if (head == nullptr || *node < *head) {
      InsertFront(head, node);
      return;
    }

    auto current = head;
    while (current->next != nullptr && *current->next < *node) {
      current = current->next;
    }

    ASSERT(!(*node < *current), "Node in wrong position");

    node->prev = current;
    node->next = current->next;
    if (current->next != nullptr) {
      current->next->prev = node;
    }
    current->next = node;
  }

  static auto Pop(Node*& head) -> Node* {
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

  static auto Remove(Node*& head, Node* nodeToRemove) -> void {
    ASSERT(head != nullptr, "Removing from empty list");
    ASSERT(nodeToRemove != nullptr, "Removing null node");

    // Handle Head-case
    if (nodeToRemove == head) {
      head = head->next;
    }

    // Re-link neighbors
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

#endif //RGBLIB_PRIORITYNODE_H
