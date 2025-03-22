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
  Log.info('\'').info(label).info("' finished in ").info(stop - start).infoLn("ms");
}

}