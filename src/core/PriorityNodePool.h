//
// Created by Brandon on 6/21/26.
//

#ifndef RGBLIB_NODEPOOL_H
#define RGBLIB_NODEPOOL_H

#include "Types.h"
#include "Assertions.h"

namespace rgb {

template<typename PriorityNode, uint N>
class PriorityNodePool {
public:
  static constexpr auto Capacity() -> uint { return N; }
  auto activeCount() const -> uint { return mActiveCount; }
  auto peakCount() const -> uint { return mPeakActiveCount; }

protected:
  PriorityNode mPool[N]{};
  PriorityNode* pInactiveHead{nullptr};
  PriorityNode* pInsertionQueueHead{nullptr};
  PriorityNode* pActiveHead{nullptr};
  uint mNextHandleId{1};
  uint mActiveCount{0};
  uint mPeakActiveCount{0};

  PriorityNodePool() {
    for (uint i = 0; i < N; ++i) {
      auto& current = mPool[i];
      current.id = i;
      current.prev = i > 0 ? &mPool[i - 1] : nullptr;
      current.next = i + 1 < N ? &mPool[i + 1] : nullptr;
    }
    pInactiveHead = &mPool[0];
    ASSERT(mPool[0].prev == nullptr, "Head invalid");
    ASSERT(mPool[N - 1].next == nullptr, "Tail invalid");
  }

  PriorityNodePool(const PriorityNodePool& rhs) = default;
  PriorityNodePool(PriorityNodePool&& rhs) noexcept = default;
  PriorityNodePool& operator=(const PriorityNodePool& rhs) = default;
  PriorityNodePool& operator=(PriorityNodePool&& rhs) noexcept = default;
  ~PriorityNodePool() = default;

  auto activate() -> PriorityNode* {
    ASSERT(pInactiveHead != nullptr, "Pool exhausted");
    if (pInactiveHead == nullptr) {
      reclaimNodes();
    }
    if (pInactiveHead == nullptr) {
      // todo - optional?
      return nullptr;
    }
    auto next = PriorityNode::Pop(pInactiveHead);
    next->clean();
    next->handleId = mNextHandleId++;
    PriorityNode::InsertFront(pInsertionQueueHead, next);
    ++mActiveCount;
    if (mActiveCount > mPeakActiveCount) {
      mPeakActiveCount = mActiveCount;
    }
    return next;
  }

  auto reclaimNodes() -> void {
    INFO("Reclaiming Timer Nodes");
    for (auto& timer : mPool) {
      if (timer.isTombstone()) {
        PriorityNode::Remove(pActiveHead, &timer);
        PriorityNode::InsertFront(pInactiveHead, &timer);
        --mActiveCount;
      }
    }
  }

  auto recycle(PriorityNode* activeNode) -> void {
    PriorityNode::InsertFront(pInsertionQueueHead, activeNode);
  }

  auto release(PriorityNode* activeNode) -> void {
    PriorityNode::InsertFront(pInactiveHead, activeNode);
    --mActiveCount;
  }
};

}

#endif //RGBLIB_NODEPOOL_H
