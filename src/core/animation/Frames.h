//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_FRAMES_H
#define RGBLIB_FRAMES_H

#include <variant>

#include "Func.h"
#include "Types.h"
#include "ForFrame.h"
#include "TimedFrame.h"
#include "WhileFrame.h"

namespace rgb {

using Frame = std::variant<TimedFrame, ForFrame, WhileFrame>;
class Frames {
public:
  static auto Wait(Duration duration) -> Frame;
  static auto Once(const TimedFrameFunction& function) -> Frame;
  static auto Of(Duration duration, const TimedFrameFunction& function) -> Frame;
  static auto For(Duration interval, u32 iterations, const ForFrameFunction& function) -> Frame;
  static auto While(const Predicate& condition, const WhileFrameFunction& function) -> Frame;
};

}

#endif //RGBLIB_FRAMES_H
