//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_EFFECTS_H
#define RGBLIB_EFFECTS_H

#include "Config.h"
#include "Types.h"
#include "Func.h"
#include "EffectHandle.h"
#include "EffectNode.h"

namespace rgb {

class PixelList;
class Effects {
  static constexpr auto EFFECT_COUNT = 10;

public:
  static auto Initialize() -> void;
  [[nodiscard]]
  static auto Start(Effect& effect, PixelList& pixels) -> EffectHandle;
  [[nodiscard]]
  static auto Start(Effect& effect, ManyPixelLists pixels) -> EffectHandle;
  static auto Stop(Effect& effect) -> void;
  static auto StopAll() -> void;

  template<typename... Args>
  static auto Stop(Effect& first, Args&... rest) -> void {
    auto& instance = Instance();
    instance.stop(first);
    (instance.stop(rest), ...);
  }
  static auto Update() -> void;
  static auto Draw() -> void;
  static auto ActiveCount() -> uint;
  static constexpr auto TotalCount() -> uint { return EFFECT_COUNT; }
  static auto Instance() -> Effects&;

  Effects();
  Effects(const Effects& rhs) = default;
  Effects(Effects&& rhs) noexcept = default;
  Effects& operator=(const Effects& rhs) = default;
  Effects& operator=(Effects&& rhs) noexcept = default;
  ~Effects() = default;

private:
  EffectNode nodes[EFFECT_COUNT]{};
  Timestamp startTime{};
  EffectNode* unusedHead{nullptr};
  EffectNode* toAddHead{nullptr};
  EffectNode* activeHead{nullptr};
  uint nextHandleId{1};

  auto initialize() -> void;
  auto start(Effect& effect, PixelList& pixels) -> EffectHandle;
  auto start(Effect& effect, ManyPixelLists pixels) -> EffectHandle;
  auto stop(Effect& effect) -> void;
  auto stopAll() -> void;
  auto update() -> void;
  auto draw() -> void;
  auto activeCount() -> uint;

  auto nextEffectNode() -> EffectNode*;
  auto enqueueForAdding(EffectNode* node) -> void;
  auto processAdditions(Timestamp now) -> void;
  auto reclaimNodes() -> void;
  auto recycle(EffectNode* timer) -> EffectNode*;
};

}


#endif //RGBLIB_EFFECTS_H
