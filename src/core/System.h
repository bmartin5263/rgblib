//
// Created by Brandon on 9/14/25.
//

#ifndef RGBLIB2_SYSTEM_H
#define RGBLIB2_SYSTEM_H

#include "Types.h"
#include "HostSystemImpl.h"

namespace rgb {

class System {
public:

  static auto MicroTime() -> microseconds_t {
    return Implementation().microTime();
  }

  static auto MilliTime() -> milliseconds_t {
    return Implementation().milliTime();
  }

  static auto MicroSleep(microseconds_t time) -> void {
    return Implementation().microSleep(time);
  }

  static auto MilliSleep(milliseconds_t time) -> void {
    return Implementation().milliSleep(time);
  }

private:
  static auto Implementation() -> priv::HostSystemImpl& {
    static System instance;
    return instance.impl;
  }
  priv::HostSystemImpl impl;
};

}

#endif //RGBLIB2_SYSTEM_H
