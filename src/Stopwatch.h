//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_STOPWATCH_H
#define RGBLIB_STOPWATCH_H

#include "Types.h"


namespace rgb {

class Stopwatch {
public:
  explicit Stopwatch(const char* label);
  ~Stopwatch();

private:
  milliseconds start;
  const char* label;
};

}


#endif //RGBLIB_STOPWATCH_H
