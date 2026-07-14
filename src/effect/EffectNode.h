//
// Created by Brandon on 1/18/26.
//

#ifndef RGBLIB_EFFECTNODE_H
#define RGBLIB_EFFECTNODE_H

#include <variant>
#include "Types.h"
#include "Assertions.h"
#include "PriorityNode.h"
#include "Effect.h"

namespace rgb {

using OnePixelList = PixelList*;
using ManyPixelLists = Iterable<PixelList*>;
using OneOrManyPixelLists = std::variant<OnePixelList, ManyPixelLists>;

class Effect;
class PixelList;
struct EffectNode : PriorityNode<EffectNode> {
  OneOrManyPixelLists pixels;
  Effect* effect;
  Timestamp startedAt{};
  uint id{};
  uint handleId{};
  uint priority{};
  bool stopping{};

  auto operator<(const EffectNode& rhs) const -> bool {
    return priority < rhs.priority;
  }

  auto clean() -> void {
    prev = nullptr;
    next = nullptr;
    pixels = {};
    effect = nullptr;
    startedAt = Timestamp::Zero();
    priority = {};
    handleId = 0;
    stopping = false;
  }

  auto start(Timestamp now) -> void {
    INFO("Starting Effect at %llu", now.asMilliseconds());
    startedAt = now;
    effect->reset(now - startedAt);
  }

  auto update(Timestamp now) -> void {
    ASSERT(effect != nullptr, "Effect is null");
    effect->update(now - startedAt);
  }

  auto draw(Timestamp now) -> void {
    ASSERT(effect != nullptr, "Effect is null");
    if (std::holds_alternative<OnePixelList>(pixels)) {
      auto& pixelList = *std::get<OnePixelList>(pixels);
      effect->draw(now - startedAt, pixelList);
    }
    else {
      auto& iterable = std::get<ManyPixelLists>(pixels);
      effect->draw(now - startedAt, iterable);
    }
  }
};

}

#endif //RGBLIB_EFFECTNODE_H
