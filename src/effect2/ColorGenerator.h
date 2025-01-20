//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_COLORGENERATOR_H
#define RGBLIB_COLORGENERATOR_H

#include "Color.h"

class ColorGenerator {
public:
  virtual auto generate() -> Color = 0;
  virtual ~ColorGenerator() = default;

private:

};


#endif //RGBLIB_COLORGENERATOR_H
