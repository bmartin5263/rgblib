//
// Created by Brandon on 1/18/26.
//

#ifndef RGBLIB_ANIMATIONNODE_H
#define RGBLIB_ANIMATIONNODE_H

#include "Types.h"
#include "PriorityNode.h"
#include "Animation.h"

namespace rgb {

class PixelList;
struct AnimationNode : PriorityNode<AnimationNode> {
  Animation* animation;
  Timestamp startedAt{};
  uint id{};
  uint handleId{};
  uint priority{};
  bool stopped{};
  bool loop{};

  auto operator<(const AnimationNode& rhs) const -> bool {
    return priority < rhs.priority;
  }

  auto clean() -> void {
    prev = nullptr;
    next = nullptr;
    animation = nullptr;
    startedAt = Timestamp{};
    priority = {};
    handleId = 0;
    stopped = false;
    loop = false;
  }

  auto update(Timestamp now) const -> bool {
    return animation->update(now - startedAt);
  }

  auto start(Timestamp time) -> void {
    startedAt = time;
  }

  auto isTombstone() -> bool {
    return stopped;
  }
};

}

#endif //RGBLIB_ANIMATIONNODE_H
