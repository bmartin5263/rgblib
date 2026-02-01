//
// Created by Brandon on 10/25/25.
//

#include "Sensor.h"

namespace rgb {

auto Sensor::read() -> void {
  doRead();
}

auto Sensor::start() -> bool {
  return doStart();
}

}