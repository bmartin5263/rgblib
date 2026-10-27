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
  static auto Chance(percent c) -> bool;

private:
  static auto Implementation() -> priv::RandomImpl&;
  priv::RandomImpl impl;
};


}


#endif //RGBLIB_RANDOM_H
