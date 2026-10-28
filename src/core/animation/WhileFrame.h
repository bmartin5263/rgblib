//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_WHILEFRAME_H
#define RGBLIB_WHILEFRAME_H

#include "Func.h"
#include "Types.h"
#include "AnimationContext.h"
#include "FrameState.h"

namespace rgb {

using WhileFrameFunction = Consumer<const WhileContext&>;

class WhileFrame {
public:
  WhileFrame(const Predicate& condition, const WhileFrameFunction& function);

  auto tryAdvance(FrameState& state) const -> FrameStatus;
  auto tick(const FrameState& state) const -> void;
  static auto finished(FrameState& state) -> void;

private:
  Predicate mCondition;
  WhileFrameFunction mFunction;
};

}

#endif //RGBLIB_WHILEFRAME_H
