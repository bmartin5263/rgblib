//
// Created by Brandon on 8/10/26.
//

#include "RandomStd.h"

namespace rgb::priv {

auto RandomStd::next() -> u32 {
  return mEngine();
}

auto RandomStd::chance(normal c) -> bool {
  auto dist = std::uniform_real_distribution{0.0f, 1.0f};
  return dist(mEngine) < c;
}
}
