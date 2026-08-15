//
// Created by Brandon on 8/15/26.
//

#include "AnimationFrame.h"


namespace rgb {
auto AnimationFrame::duration() const -> Duration {
  return mDuration;
}

auto AnimationFrame::operator()(normal percentComplete) const -> void {
  auto context = AnimationContext{percentComplete};
  mFunction(context);
}

}
