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
  uint id{};
  uint handleId{};
  uint priority{};
  bool stopped{};
  bool loop{};
  bool firstUpdate{};

  auto operator<(const AnimationNode& rhs) const -> bool {
    return priority < rhs.priority;
  }

  auto clean() -> void {
    prev = nullptr;
    next = nullptr;
    animation = nullptr;
    priority = {};
    handleId = 0;
    stopped = false;
    loop = false;
    firstUpdate = false;
  }

  auto update(Duration delta) -> bool {
    // Set delta to 0 for the first update since the delta is measuring a window the animation was inactive for
    auto result = animation->update(firstUpdate ? delta : Duration::Zero());
    firstUpdate = true;
    return result;
  }

  auto start() -> void {
    firstUpdate = false;
    animation->reset();
  }

  auto isTombstone() const -> bool {
    return stopped;
  }
};

}

#endif //RGBLIB_ANIMATIONNODE_H
