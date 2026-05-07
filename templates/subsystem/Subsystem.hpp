//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_SUBSYSTEM_H
#define RGBLIB_SUBSYSTEM_H

namespace rgb {

class Subsystem {
public:
  auto DoSomething() -> int;

private:
  static auto Implementation() -> priv::SubsystemImpl&;
  priv::SubsystemImpl impl;
};

auto Subsystem::Implementation() -> priv::SubsystemImpl& {
  static Subsystem instance;
  return instance.impl;
}

auto Subsystem::DoSomething() -> int {
  return Implementation().doSomething();
}

}

#endif //RGBLIB_SUBSYSTEM_H
