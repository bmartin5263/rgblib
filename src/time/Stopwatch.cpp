//
// Created by Brandon on 3/20/25.
//

#include "Clock.h"
#include "Stopwatch.h"
#include "Log.h"

namespace rgb {

Stopwatch::Stopwatch(const char* label): start(Clock::Milli()), label(label) {

}

Stopwatch::~Stopwatch() {
  auto stop = Clock::Milli();
  auto duration = stop - start;
  INFO("'%s' finished in %lums", label, duration);
}

}