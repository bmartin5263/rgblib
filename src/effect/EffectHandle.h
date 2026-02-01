//
// Created by Brandon on 3/25/25.
//

#ifndef RGBLIB_EFFECTHANDLE_H
#define RGBLIB_EFFECTHANDLE_H

#include <memory>
#include "Handle.h"
#include "Func.h"

namespace rgb {

struct EffectNode;
class EffectHandle {
public:
  EffectHandle();
  explicit EffectHandle(EffectNode* node);
  EffectHandle(const EffectHandle& rhs) = delete;
  EffectHandle(EffectHandle&& rhs) noexcept;
  EffectHandle& operator=(const EffectHandle& rhs) = delete;
  EffectHandle& operator=(EffectHandle&& rhs) noexcept;
  ~EffectHandle();

  // Release ownership without stopping the effect
  auto detach() -> void;

  // Release ownership and stop the effect
  auto stop() -> void;

  auto isRunning() -> bool;

  auto operator==(const EffectHandle& rhs) const -> bool {
    return node == rhs.node && handleId == rhs.handleId;
  }

  auto operator!=(const EffectHandle& rhs) const -> bool {
    return !(*this == rhs);
  }

  uint handleId;
  EffectNode* node;
};

}

#endif //RGBLIB_EFFECTHANDLE_H
