//
// Created by Brandon on 1/8/25.
//

#ifndef RGBLIB_COLORGENERATOR_H
#define RGBLIB_COLORGENERATOR_H

#include "core/Types.h"
#include "led/Color.h"
#include "Parameters.h"

class LEDChain;
class ColorGenerator {
public:

  virtual auto generate(const Parameters& params) -> Color const = 0;

  virtual ~ColorGenerator() = default;
};


#endif //RGBLIB_COLORGENERATOR_H
