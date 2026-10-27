//
// Created by Brandon on 10/26/26.
//

#include "Random.h"

namespace rgb {

auto Random::Implementation() -> priv::RandomImpl& {
  static Random instance;
  return instance.impl;
}

auto Random::Next() -> u32 {
  return Implementation().next();
}

auto Random::Chance(percent c) -> bool {
  return Implementation().chance(c);
}
}
