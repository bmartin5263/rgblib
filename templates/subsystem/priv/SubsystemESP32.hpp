//
// Created by Brandon on 10/6/25.
//

#ifndef RGBLIB_SUBSYSTEMESP32_H
#define RGBLIB_SUBSYSTEMESP32_H

#include "SubsystemBase.hpp"

namespace rgb::priv {

class SubsystemESP32 : public SubsystemBase {
public:
  auto doSomething() -> int;

private:

};

auto SubsystemESP32::doSomething() -> int {
  return 0;
}

}

#endif //RGBLIB_SUBSYSTEMESP32_H
