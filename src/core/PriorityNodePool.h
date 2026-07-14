//
// Created by Brandon on 6/21/26.
//

#ifndef RGBLIB_NODEPOOL_H
#define RGBLIB_NODEPOOL_H

#include "Types.h"
#include "Assertions.h"
#include "PriorityNode.h"

namespace rgb {

template<typename PriorityNode, uint Count>
class PriorityNodePool {
public:
  static constexpr auto TotalCount() -> uint { return Count; }

protected:
  PriorityNode nodes[Count]{};
  PriorityNode* unusedHead{nullptr};
  PriorityNode* toAddHead{nullptr};
  PriorityNode* activeHead{nullptr};
  uint nextHandleId{1};

  PriorityNodePool() {
    for (uint i = 0; i < Count; ++i) {
      auto& current = nodes[i];
      current.id = i;
      current.prev = i > 0 ? &nodes[i - 1] : nullptr;
      current.next = i + 1 < Count ? &nodes[i + 1] : nullptr;
    }
    unusedHead = &nodes[0];
    ASSERT(nodes[0].prev == nullptr, "Head invalid");
    ASSERT(nodes[Count - 1].next == nullptr, "Tail invalid");
  }

  PriorityNodePool(const PriorityNodePool& rhs) = default;
  PriorityNodePool(PriorityNodePool&& rhs) noexcept = default;
  PriorityNodePool& operator=(const PriorityNodePool& rhs) = default;
  PriorityNodePool& operator=(PriorityNodePool&& rhs) noexcept = default;
  ~PriorityNodePool() = default;

  auto popUnused() -> PriorityNode* {
    ASSERT_C(unusedHead != nullptr, "No more nodes available", Color::WHITE());
    auto next = PriorityNode::Pop(unusedHead);
    ASSERT(next->next == nullptr, "Next is not a nullptr");
    ASSERT(next->prev == nullptr, "Prev is not a nullptr");
    return next;
  }

  auto enqueueForAdding(PriorityNode* node) -> void {
    ASSERT(node->next == nullptr, "Next is not nullptr");
    ASSERT(node->prev == nullptr, "Prev is not nullptr");
    PriorityNode::InsertFront(toAddHead, node);
  }
};

}

#endif //RGBLIB_NODEPOOL_H
