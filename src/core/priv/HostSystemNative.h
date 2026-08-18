//
// Created by Brandon on 8/17/26.
//

#ifndef RGBLIB_HOSTSYSTEMNATIVE_H
#define RGBLIB_HOSTSYSTEMNATIVE_H

#include <chrono>
#include <thread>
#include "Types.h"
#include "HostSystemBase.h"

namespace rgb::priv {

class HostSystemNative : public HostSystemBase {
public:
  auto microTime() -> microseconds_t {
    auto now = std::chrono::steady_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(now).count();
  }

  auto milliTime() -> milliseconds_t {
    return microTime() / 1000;
  }

  auto microSleep(microseconds_t time) -> void {
    std::this_thread::sleep_for(std::chrono::microseconds(time));
  }

  auto milliSleep(milliseconds_t time) -> void {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
  }
};


}

#endif //RGBLIB_HOSTSYSTEMNATIVE_H
