//
// Created by Brandon on 1/18/26.
//

#ifndef RGBLIB_EFFECTNODE_H
#define RGBLIB_EFFECTNODE_H

#include <variant>
#include "Types.h"
#include "Assertions.h"
#include "Effect.h"

namespace rgb {

using OnePixelList = PixelList*;
using ManyPixelLists = Iterable<PixelList*>;
using OneOrManyPixelLists = std::variant<OnePixelList, ManyPixelLists>;

class Effect;
class PixelList;
struct EffectNode {
  EffectNode* prev{};
  EffectNode* next{};
  OneOrManyPixelLists pixels;
  Effect* effect;
  Timestamp startedAt{};
  uint id{};
  uint handleId{};
  uint priority{};
  bool stopping{};

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

  static auto Size(EffectNode* head) -> uint {
    auto result = 0u;
    while (head != nullptr) {
      ++result;
      head = head->next;
    }
    return result;
  }

  static auto InsertFront(EffectNode*& head, EffectNode* node) {
    ASSERT(node->next == nullptr, "Next is not nullptr");
    ASSERT(node->prev == nullptr, "Prev is not nullptr");

    node->prev = nullptr;
    node->next = head;
    if (head != nullptr) {
      head->prev = node;
    }
    head = node;
  }

  static auto Pop(EffectNode*& head) -> EffectNode* {
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

  static auto Remove(EffectNode*& head, EffectNode* nodeToRemove) -> void {
    ASSERT(head != nullptr, "Removing from empty list");
    ASSERT(nodeToRemove != nullptr, "Removing null node");

    if (nodeToRemove == head) {
      head = head->next;
      nodeToRemove->next = nullptr;
      nodeToRemove->prev = nullptr;
      return;
    }

    if (nodeToRemove->next != nullptr) {
      nodeToRemove->next->prev = nodeToRemove->prev;
    }
    if (nodeToRemove->prev != nullptr) {
      nodeToRemove->prev->next = nodeToRemove->next;
    }
  }
};

}

#endif //RGBLIB_EFFECTNODE_H
