//
// Created by Brandon on 8/9/26.
//

#ifndef RGBLIB_RANDOMSTD_H
#define RGBLIB_RANDOMSTD_H

#include <random>
#include "RandomBase.h"
#include "Types.h"

namespace rgb::priv {

class RandomStd : public RandomBase {
public:
  auto next() -> u32;

private:
  std::mt19937 mEngine{std::random_device{}()};
};

}
#endif //RGBLIB_RANDOMSTD_H
