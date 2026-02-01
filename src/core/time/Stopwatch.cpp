//
// Created by Brandon on 3/20/25.
//

#include "System.h"
#include "Stopwatch.h"
#include "Log.h"

namespace rgb {

Stopwatch::Stopwatch(const char* label): start(System::MilliTime()), label(label) {

}

Stopwatch::~Stopwatch() {
  auto stop = System::MilliTime();
  auto duration = stop - start;
  INFO("'%s' finished in %llums", label, duration);
}

}