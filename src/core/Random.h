//
// Created by Brandon on 8/9/26.
//

#ifndef RGBLIB_RANDOM_H
#define RGBLIB_RANDOM_H

#include "RandomImpl.h"
#include "Types.h"

namespace rgb {

class Random {
public:
  static auto Next() -> u32;

private:
  static auto Implementation() -> priv::RandomImpl&;
  priv::RandomImpl impl;
};

inline auto Random::Implementation() -> priv::RandomImpl& {
  static Random instance;
  return instance.impl;
}

inline auto Random::Next() -> u32 {
  return Implementation().next();
}

}


#endif //RGBLIB_RANDOM_H
