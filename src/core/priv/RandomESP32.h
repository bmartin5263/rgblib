//
// Created by Brandon on 8/9/26.
//

#ifndef RGBLIB_RANDOMESP32_H
#define RGBLIB_RANDOMESP32_H

#include "RandomBase.h"
#include "Types.h"

namespace rgb::priv {

class RandomESP32 : public RandomBase {
public:
  auto next() -> u32;
};

}
#endif //RGBLIB_RANDOMESP32_H
