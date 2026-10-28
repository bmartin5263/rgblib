//
// Created by Brandon on 8/15/26.
//

#ifndef RGBLIB_ANIMATIONCONTEXT_H
#define RGBLIB_ANIMATIONCONTEXT_H

#include "Types.h"

namespace rgb {

struct TimedContext {
  normal percentComplete{};
};

class ForContext {
public:
  constexpr ForContext(u32 index, u32 iterations) : mIndex(index), mIterations(iterations) {}

  constexpr auto index() const -> u32 { return mIndex; }
  constexpr auto iterations() const -> u32 { return mIterations; }

  // 0.0 on the first iteration, 1.0 on the last
  constexpr auto percentComplete() const -> normal {
    if (mIterations <= 1) {
      return 1.0f;
    }
    return static_cast<normal>(mIndex) / static_cast<normal>(mIterations - 1);
  }

private:
  u32 mIndex;
  u32 mIterations;
};

class WhileContext {
public:
  constexpr explicit WhileContext(Duration elapsed) : mElapsed(elapsed) {}

  constexpr auto elapsed() const -> Duration { return mElapsed; }

private:
  Duration mElapsed;
};

}

#endif //RGBLIB_ANIMATIONCONTEXT_H
